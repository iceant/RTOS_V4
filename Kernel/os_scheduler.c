#include <os_scheduler.h>
#include <os_interrupt.h>
#include <os_readylist.h>
#include <os_lock.h>
#include <assert.h>
#include <os_timewheel.h>
#include <cpu.h>
#include <os_service.h>
/* -------------------------------------------------------------------------------------------------------------- */
/* EXTERNAL  */

volatile os_thread_t * os_scheduler_current_thread_p;
volatile os_tick_t     os_scheduler__systick_tick;
/* -------------------------------------------------------------------------------------------------------------- */
/* STATIC */
static os_thread_t *    os_scheduler__highest_thread_p;

static os_size_t        os_scheduler__lock_nesting;
static os_int_t         os_scheduler__schedule_flag;
static os_list_t        os_scheduler__wait_list;
static int              os_scheduler__startup_flag;
static int              os_scheduler__need_schedule_flag;

/* -------------------------------------------------------------------------------------------------------------- */
/* UTILS */

#define OS_SCHEDULER_LOCK_VAR() os_lock_t os_scheduler__lock=0
#define OS_SCHEDULER_LOCK_LOCK() os_lock_lock(&os_scheduler__lock)
#define OS_SCHEDULER_LOCK_UNLOCK() os_lock_unlock(&os_scheduler__lock)

/* -------------------------------------------------------------------------------------------------------------- */
/* STATIC METHODS */

C_STATIC_FORCE_INLINE void os_scheduler__yield(os_thread_t* thread){
    thread->state = OS_THREAD_STATE_YIELD;
    thread->remain_ticks = 0;
    OS_LIST_INSERT_BEFORE(&os_scheduler__wait_list, &thread->ready_node);
}

static void os_scheduler__task_switch_callback(void** from_stack_p, void** to_stack_p){
    os_scheduler_current_thread_p = os_scheduler__highest_thread_p;
    os_scheduler_current_thread_p->state = OS_THREAD_STATE_RUNNING;
    os_scheduler_current_thread_p->remain_ticks = os_scheduler_current_thread_p->init_tick;
    os_scheduler__schedule_flag = OS_SCHEDULER_FLAG_NONE;
}

static void os_scheduler__timeout(os_timer_t* timer){
    os_thread_t* thread = (os_thread_t*)timer->userdata;
    os_readylist_push_back(thread);
    thread->error = OS_ERR_TIMEOUT;
}
/* -------------------------------------------------------------------------------------------------------------- */
/* METHDO */

os_err_t os_scheduler_init(void)
{
    os_scheduler__startup_flag = 0;
    
    os_scheduler_current_thread_p = 0;
    os_scheduler__highest_thread_p = 0;
    os_scheduler__systick_tick = 0;
    os_scheduler__lock_nesting = 0;
    OS_LIST_INIT(&os_scheduler__wait_list);
    os_scheduler__need_schedule_flag = 0;
    
    return OS_ERR_OK;
}

os_err_t os_scheduler_startup(void){
    if(os_scheduler__startup_flag==1) return OS_ERR_ERROR;
    os_scheduler__startup_flag = 1;
    return os_scheduler_schedule();
}

volatile os_thread_t* os_scheduler_current_thread(void){
    return os_scheduler_current_thread_p;
}

static os_err_t os_scheduler__yield_status;
os_err_t os_scheduler_yield(os_thread_t* thread){
    OS_SCHEDULER_LOCK_VAR();
    OS_SCHEDULER_LOCK_LOCK();
    os_scheduler__yield(thread);
    OS_SCHEDULER_LOCK_UNLOCK();
    os_scheduler__yield_status = os_scheduler_schedule();
    return os_scheduler__yield_status;
}

void os_scheduler_disable(void){
    OS_SCHEDULER_LOCK_VAR();
    OS_SCHEDULER_LOCK_LOCK();
    os_scheduler__lock_nesting++;
    OS_SCHEDULER_LOCK_UNLOCK();
}

void os_scheduler_enable(void){
    OS_SCHEDULER_LOCK_VAR();
    OS_SCHEDULER_LOCK_LOCK();
    os_scheduler__lock_nesting--;
    OS_SCHEDULER_LOCK_UNLOCK();
}

void os_scheduler_wait(os_thread_t* thread){
    OS_SCHEDULER_LOCK_VAR();
    OS_SCHEDULER_LOCK_LOCK();
    OS_LIST_INSERT_BEFORE(&os_scheduler__wait_list, &thread->ready_node);
    OS_SCHEDULER_LOCK_UNLOCK();
}

os_bool_t os_scheduler_is_need_schedule(void){
    return os_scheduler__need_schedule_flag==1;
}

void os_scheduler_set_need_schedule(int flag){
    os_scheduler__need_schedule_flag = flag;
}

os_err_t os_scheduler_schedule(void){
    OS_SCHEDULER_LOCK_VAR();
    
    if(os_scheduler__startup_flag==0){
        return OS_SCHEDULER_ERR_NOT_START;
    }
    
    if(os_interrupt_is_nest()){
        return OS_SCHEDULER_ERR_INT_NEST;
    }
    
    if(os_scheduler__lock_nesting>0u){
        return OS_SCHEDULER_ERR_DISABLED;
    }
    
    OS_SCHEDULER_LOCK_LOCK();
    
    if(os_scheduler__schedule_flag==OS_SCHEDULER_FLAG_WIP){
        OS_SCHEDULER_LOCK_UNLOCK();
        return OS_SCHEDULER_ERR_WIP;
    }
    os_scheduler__schedule_flag = OS_SCHEDULER_FLAG_WIP;
    
    os_scheduler__highest_thread_p = os_readylist_pop();
    if(os_scheduler__highest_thread_p==0){
        os_scheduler__schedule_flag = OS_SCHEDULER_FLAG_NONE;
        OS_SCHEDULER_LOCK_UNLOCK();
        return OS_SCHEDULER_ERR_NOTHREAD;
    }else if(os_scheduler__highest_thread_p->init_priority==OS_THREAD_IDLE_PRIORITY){
        /* IDLE 线程永远在就绪表中 */
        os_readylist_push_back(os_scheduler__highest_thread_p);
    }
    
    if(!OS_LIST_IS_EMPTY(&os_scheduler__wait_list)){
        /* 将等待的任务加入就绪表 */
        os_list_node_t *node;
        os_thread_t* wait_thread_p;
        for(node = OS_LIST_NEXT(&os_scheduler__wait_list); node!=&os_scheduler__wait_list; ){
            wait_thread_p = OS_LIST_CONTAINER(node, os_thread_t, ready_node);
            node = OS_LIST_NEXT(node);
            os_readylist_push_back(wait_thread_p);
        }
        assert(OS_LIST_IS_EMPTY(&os_scheduler__wait_list));
    }
    
    if(os_scheduler__highest_thread_p==os_scheduler_current_thread_p){
        os_scheduler__schedule_flag = OS_SCHEDULER_FLAG_NONE;
        OS_SCHEDULER_LOCK_UNLOCK();
        return OS_SCHEDULER_ERR_SAME_AS_CURRENT_THREAD;
    }
    
    if(os_scheduler_current_thread_p){
        if(os_scheduler_current_thread_p->state==OS_THREAD_STATE_RUNNING){
            if(os_priority_cmp(os_scheduler_current_thread_p->current_priority
                    , os_scheduler__highest_thread_p->current_priority)!=OS_PRIORITY_CMP_LOW){
                /* 当前任务优先级不低于要调度的任务，具有继续执行的权利 */
                os_readylist_push_front(os_scheduler__highest_thread_p);
                os_scheduler__schedule_flag = OS_SCHEDULER_FLAG_NONE;
                OS_SCHEDULER_LOCK_UNLOCK();
                return OS_SCHEDULER_ERR_CURRENT_THREAD_RUNNING;
            }else{
                /*抢占*/
                os_readylist_push_back((os_thread_t*)os_scheduler_current_thread_p);
            }
        }
    }
    
    /*Unlock, IMPORTANT!!!*/
    OS_SCHEDULER_LOCK_UNLOCK();
    
    int err = cpu_stack_switch((void**)(os_scheduler_current_thread_p==0?0:&os_scheduler_current_thread_p->sp)
            , &os_scheduler__highest_thread_p->sp
            , os_scheduler__task_switch_callback);
    
    if(err!=CPU_STACK_OK){
        OS_SCHEDULER_LOCK_LOCK();
        os_readylist_push_front(os_scheduler__highest_thread_p); /*调度失败，重新放回就绪表，等待下次调度*/    
        os_scheduler__schedule_flag = OS_SCHEDULER_FLAG_NONE;
        OS_SCHEDULER_LOCK_UNLOCK();
        return OS_SCHEDULER_ERR_RETRY;
    }
    
   
    OS_SCHEDULER_LOCK_UNLOCK();
    return OS_ERR_OK;
}

os_err_t os_scheduler_systick(void){
    OS_SCHEDULER_LOCK_VAR();
    
    if(os_scheduler__startup_flag==0){
        return OS_SCHEDULER_ERR_NOT_START;
    }
    
    if(os_scheduler__lock_nesting>0u){
        return OS_SCHEDULER_ERR_DISABLED;
    }
    
    OS_SCHEDULER_LOCK_LOCK();
    os_scheduler__systick_tick++;
    
    if(os_scheduler_current_thread_p){
        if(os_scheduler_current_thread_p->state==OS_THREAD_STATE_RUNNING){
            if(os_scheduler_current_thread_p->remain_ticks>0u){
                os_scheduler_current_thread_p->remain_ticks--;
            }
            
            if(os_scheduler_current_thread_p->remain_ticks==0u){
                os_scheduler__yield((os_thread_t*)os_scheduler_current_thread_p);
                os_scheduler__need_schedule_flag = 1;
            }
        }
    }
    
    if(os_timewheel_tick()==OS_TIMEWHEEL_ERR_NEED_SCHEDULE){
        os_scheduler__need_schedule_flag = 1;
    }
    
    OS_SCHEDULER_LOCK_UNLOCK();
    return OS_ERR_OK;
}

os_err_t os_scheduler_resume(os_thread_t* thread){
    OS_SCHEDULER_LOCK_VAR();
    OS_SCHEDULER_LOCK_LOCK();
    os_readylist_push_back(thread);
    OS_SCHEDULER_LOCK_UNLOCK();
    return os_service_schedule();
}

os_err_t os_scheduler_delay(os_thread_t* thread, os_tick_t ticks){
    OS_SCHEDULER_LOCK_VAR();
    OS_SCHEDULER_LOCK_LOCK();
    os_timewheel_add_timer(&thread->timer, os_scheduler__timeout, thread, ticks, OS_TIMER_FLAG_ONCE);
    thread->state = OS_THREAD_STATE_DELAY;
    thread->error = OS_ERR_OK;
    OS_SCHEDULER_LOCK_UNLOCK();
    return os_service_schedule();
}

os_err_t os_scheduler_delay_no_schedule(os_thread_t* thread, os_tick_t ticks){
    os_timewheel_add_timer(&thread->timer, os_scheduler__timeout, thread, ticks, OS_TIMER_FLAG_ONCE);
    thread->state = OS_THREAD_STATE_DELAY;
    thread->error = OS_ERR_OK;
    return OS_ERR_OK;
}
