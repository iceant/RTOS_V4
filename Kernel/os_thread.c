#include <os_thread.h>
#include <os_memory.h>
#include <os_macros.h>
#include <cpu.h>
#include <os_scheduler.h>
#include "os_service.h"

/* -------------------------------------------------------------------------------------------------------------- */
/* STATIC */

static void os_thread__exit(void){
    os_thread_t* thread = os_thread_self();
    thread->state = OS_THREAD_STATE_DIED;
    OS_LIST_REMOVE(&thread->ready_node);
    OS_LIST_REMOVE(&thread->pend_node);
    OS_LIST_REMOVE(&thread->timer.wait_node);
    if(thread->exit_entry){
        thread->exit_entry(thread);
    }
    os_service_schedule();
}

/* -------------------------------------------------------------------------------------------------------------- */
/* METHODS */

os_err_t os_thread_init(os_thread_t* thread
        , const char* name
        , os_thread_entry_t start_entry
        , void* parameter
        , uint8_t* stack_address
        , os_size_t stack_size
        , os_priority_t init_priority
        , os_tick_t init_tick
        , void (*exit_entry)(os_thread_t*)
        , int flag
){
    
    os_size_t name_size = strlen(name);
    name_size = OS_MIN(name_size, OS_NAME_MAX_SIZE-1);
    memcpy(thread->name, name, name_size);
    thread->name[name_size]='\0';
    
    thread->start_entry = start_entry;
    thread->parameter= parameter;
    thread->stack_address = stack_address;
    thread->stack_size = stack_size;
    thread->exit_entry = exit_entry;
    thread->init_tick = init_tick;
    thread->init_priority = init_priority;
    thread->current_priority = init_priority;
    thread->flag = flag;
    thread->error = OS_ERR_OK;
    
    OS_LIST_INIT(&thread->ready_node);
    OS_LIST_INIT(&thread->pend_node);
    OS_LIST_INIT(&thread->timer.wait_node);
    
    cpu_stack_init(start_entry, parameter
                   , stack_address, (cpu_int_t)stack_size
                   , os_thread__exit, &thread->sp);
    
    thread->state = OS_THREAD_STATE_SUSPEND;
    return OS_ERR_OK;
}

os_err_t os_thread_startup(os_thread_t* thread){
    return os_service_resume(thread);
}

os_thread_t * os_thread_self(void){
    return (os_thread_t*)os_scheduler_current_thread_p;
}

void os_thread_yield(void){
    os_service_yield((os_thread_t*)os_scheduler_current_thread_p);
}

void os_thread_delay(os_tick_t ticks){
    os_service_delay((os_thread_t*)os_scheduler_current_thread_p, ticks);
}

void os_thread_mdelay(os_uint_t ms){
    os_service_delay((os_thread_t*)os_scheduler_current_thread_p, os_tick_from_millisecond(ms));
}

