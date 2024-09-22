#include <os_mutex.h>
#include "os_service.h"

os_err_t os_mutex_init(os_mutex_t* mutex, int flag){
    os_waitobject_init(&mutex->wait_object, flag);
    cpu_spinlock_init(&mutex->lock);
    mutex->owner = 0;
    mutex->hold = 0;
    return OS_ERR_OK;
}

os_err_t os_mutex_lock(os_mutex_t* mutex, os_tick_t ticks){
    cpu_uint_t status;
    os_thread_t* current_thread = os_thread_self();
    if(mutex->owner == current_thread){
        mutex->hold++;
        return OS_ERR_OK;
    }
    do{
        status = cpu_spinlock_try_lock(&mutex->lock);
        if(status!=0){
            /*没有获得锁, 当前线程等待*/
            if(os_priority_cmp(mutex->owner->current_priority, current_thread->current_priority)==OS_PRIORITY_CMP_LOW){
                /* 当前任务的优先级比较低，提升优先级 */
                mutex->owner->current_priority = current_thread->current_priority;
            }
            os_err_t wait_error = os_service_wait(&mutex->wait_object, os_thread_self(), ticks);
            if(wait_error==OS_ERR_TIMEOUT){
                return OS_ERR_TIMEOUT;
            }
        }
    }while(status!=0);
    /*到这里表示已经获得了锁*/
    mutex->owner = current_thread;
    mutex->hold = 1;
    return OS_ERR_OK;
}

os_err_t os_mutex_unlock(os_mutex_t* mutex){
    os_thread_t* current_thread = os_thread_self();
    if(mutex->owner!=current_thread){
        return OS_MUTEX_ERR_NOT_OWNER;
    }
    mutex->hold--;
    if(mutex->hold==0){
        /* 释放锁，恢复owner的优先级 */
        mutex->owner->current_priority = mutex->owner->init_priority;
        mutex->owner = 0;
        cpu_spinlock_unlock(&mutex->lock);
        os_service_notify_all(&mutex->wait_object);
        return OS_ERR_OK;
    }
    return OS_MUTEX_ERR_OWNER_HOLD;
}

