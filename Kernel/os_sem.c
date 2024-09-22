#include <os_sem.h>
#include <os_waitobject.h>
#include <string.h>
#include <os_macros.h>
#include <os_service.h>
#include <os_scheduler.h>
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
    do{
        if(sem->value>0){
            sem->value--;
            return OS_ERR_OK;
        }
        wait_error = os_service_wait(&sem->wait_object, os_thread_self(), wait_for_ticks);
    } while (wait_error!=OS_ERR_OK && wait_error!=OS_ERR_TIMEOUT);
    
    return wait_error;
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


