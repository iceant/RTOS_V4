#include <os_waitobject.h>
#include <os_lock.h>
#include <os_scheduler.h>
#include <os_readylist.h>
#include <stdio.h>
#include "os_service.h"
#include "os_timewheel.h"
/* -------------------------------------------------------------------------------------------------------------- */
/* STATIC */
C_STATIC_FORCE_INLINE void os_waitobject_push_back(os_waitobject_t* object, os_thread_t* thread){
    os_list_node_t * node;
    os_thread_t * thread_p;
    
    OS_LIST_REMOVE(&thread->pend_node);
    
    if(object->flag==OS_WAIT_FLAG_PRIO){
        for(node = OS_LIST_NEXT(&object->wait_list); node!=&object->wait_list; ){
            thread_p = OS_LIST_CONTAINER(node, os_thread_t, pend_node);
            node = OS_LIST_NEXT(node);
            
            if(os_priority_cmp(thread->current_priority, thread_p->current_priority)==OS_PRIORITY_CMP_HIGH){
                OS_LIST_INSERT_BEFORE(&thread_p->pend_node, &thread->pend_node);
                return;
            }
        }
        OS_LIST_INSERT_BEFORE(&object->wait_list, &thread->pend_node);
    }else{
        OS_LIST_INSERT_BEFORE(&object->wait_list, &thread->pend_node);
    }
}

C_STATIC_FORCE_INLINE void os_waitobject_pop_one(os_waitobject_t* object) {
    os_list_node_t *node;
    if (OS_LIST_IS_EMPTY(&object->wait_list)) {
        return;
    }
    node = OS_LIST_NEXT(&object->wait_list);
    os_thread_t *thread = OS_LIST_CONTAINER(node, os_thread_t, pend_node);
    OS_LIST_REMOVE(&thread->pend_node);
    os_timewheel_remove_timer(&thread->timer);
    os_readylist_push_back(thread);
}

C_STATIC_FORCE_INLINE void os_waitobject_pop_all(os_waitobject_t* object){
    os_list_node_t *node;
    os_thread_t* thread;
    if (OS_LIST_IS_EMPTY(&object->wait_list)) {
        return;
    }
    for(node= OS_LIST_NEXT(&object->wait_list); node!=&object->wait_list; ){
        thread = OS_LIST_CONTAINER(node, os_thread_t, pend_node);
        node = OS_LIST_NEXT(node);
        OS_LIST_REMOVE(&thread->pend_node);
        os_timewheel_remove_timer(&thread->timer);
        os_readylist_push_back(thread);
    }
}
/* -------------------------------------------------------------------------------------------------------------- */
/* METHOD */

os_err_t os_waitobject_init(os_waitobject_t* object, int flag)
{
    object->flag = flag;
    OS_LIST_INIT(&object->wait_list);
    return OS_ERR_OK;
}

os_err_t os_waitobject_wait(os_waitobject_t * object, os_thread_t *thread, os_tick_t wait_ticks){
    os_lock_t lock;
    os_lock_init(&lock);
    os_lock_lock(&lock);
    
    if(wait_ticks==0){
        os_lock_unlock(&lock);
        return OS_ERR_TIMEOUT;
    }else if(wait_ticks==OS_WAIT_FOREVER){
        OS_LIST_REMOVE(&thread->pend_node);
        OS_LIST_INSERT_BEFORE(&object->wait_list, &thread->pend_node);
        os_lock_unlock(&lock);
        return os_scheduler_schedule();
    }else {
        os_scheduler_delay_no_schedule(thread, wait_ticks);
        OS_LIST_REMOVE(&thread->pend_node);
        OS_LIST_INSERT_BEFORE(&object->wait_list, &thread->pend_node);
        os_lock_unlock(&lock);
        os_scheduler_schedule();
        if(thread->error==OS_ERR_TIMEOUT){
            thread->error = OS_ERR_OK; /* 超时了还没被唤醒 */
            return OS_ERR_TIMEOUT;
        }
        return OS_ERR_OK; /*超时之前被唤醒了*/
    }
}

os_err_t os_waitobject_notify_one(os_waitobject_t* object){
    os_lock_t lock;
    os_lock_init(&lock);
    os_lock_lock(&lock);
    os_waitobject_pop_one(object);
    os_lock_unlock(&lock);
    return os_scheduler_schedule();
}

os_err_t os_waitobject_notify_all(os_waitobject_t* object){
    os_lock_t lock;
    os_lock_init(&lock);
    os_lock_lock(&lock);
    os_waitobject_pop_all(object);
    os_lock_unlock(&lock);
    return os_scheduler_schedule();
}
