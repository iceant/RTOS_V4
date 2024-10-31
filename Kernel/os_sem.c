#include <os_sem.h>
#include <os_waitobject.h>
#include <string.h>
#include <os_macros.h>
#include <os_service.h>
#include <os_scheduler.h>
#include <stdio.h>
#include <os_lock.h>
/* -------------------------------------------------------------------------------------------------------------- */
/* METHODS */

os_err_t os_sem_init(os_sem_t* sem, const char* name, os_uint_t init_value, int flag){
    os_waitobject_init(&sem->wait_object, flag);
    
    sem->value = init_value;
    
    os_size_t name_size = strlen(name);
    name_size = OS_MIN(name_size, OS_NAME_MAX_SIZE-1);
    memcpy(sem->name, name, name_size);
    sem->name[name_size]='\0';
    
    return OS_ERR_OK;
}

os_err_t os_sem_take(os_sem_t * sem, os_tick_t wait_for_ticks){
    os_err_t wait_error = 0;
//    do{
//        if(sem->value>0){
//            sem->value--;
//            return OS_ERR_OK;
//        }
//        wait_error = os_service_wait(&sem->wait_object, os_thread_self(), wait_for_ticks);
//        if(wait_error==OS_ERR_TIMEOUT) {
//            return wait_error;
//        }
//    } while (1);
    
    os_lock_t lock;
    os_thread_t * thread = os_thread_self();
    
    if(sem->value>0){
        sem->value--;
        return OS_ERR_OK;
    }
    
    os_lock_init(&lock);
    
    do{
        os_lock_lock(&lock);
        
        if(wait_for_ticks==0){
            os_lock_unlock(&lock);
            return OS_ERR_TIMEOUT;
        }else if(wait_for_ticks==OS_WAIT_FOREVER){
            OS_LIST_REMOVE(&thread->pend_node);
            OS_LIST_INSERT_BEFORE(&sem->wait_object.wait_list, &thread->pend_node);
            os_lock_unlock(&lock);
            os_service_schedule();
        }else {
            os_scheduler_delay_no_schedule(thread, wait_for_ticks);
            os_lock_unlock(&lock);
            os_err_t err = os_service_schedule();/*在 SVC 中时，调度不会发生，造成直接执行了下面的语句*/
            if(thread->error==OS_ERR_TIMEOUT){
                thread->error = OS_ERR_OK; /* 超时了还没被唤醒 */
                if(sem->value>0){
                    sem->value--;
                    return OS_ERR_OK;
                }
                return OS_ERR_TIMEOUT;
            }
        }
        
        if(sem->value>0){
            sem->value--;
            return OS_ERR_OK;
        }
    }while(1);
    
}

os_err_t os_sem_release(os_sem_t* sem){
//    cpu_spinlock_lock(&sem->lock); /* lock used in IRQ will cause deadlock */
    sem->value++;
//    cpu_spinlock_unlock(&sem->lock);
    os_err_t err = os_service_notify(&sem->wait_object);
    if(err!=OS_ERR_OK){
        os_scheduler_set_need_schedule(1);
    }
    return err;
}


