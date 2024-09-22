#ifndef INCLUDED_OS_THREAD_H
#define INCLUDED_OS_THREAD_H

/* -------------------------------------------------------------------------------------------------------------- */
/* DEPENDENCIES */

#ifndef INCLUDED_OS_TYPES_H
#include <os_types.h>
#endif /*INCLUDED_OS_TYPES_H*/

#ifndef INCLUDED_OS_TICK_H
#include <os_tick.h>
#endif /*INCLUDED_OS_TICK_H*/

#ifndef INCLUDED_OS_PRIORITY_H
#include <os_priority.h>
#endif /*INCLUDED_OS_PRIORITY_H*/

#ifndef INCLUDED_OS_LIST_H
#include <os_list.h>
#endif /*INCLUDED_OS_LIST_H*/

#ifndef INCLUDED_OS_TIMER_H
#include <os_timer.h>
#endif /*INCLUDED_OS_TIMER_H*/



/* -------------------------------------------------------------------------------------------------------------- */
/* TYPES */

#define OS_THREAD_STATE_SUSPEND             1
#define OS_THREAD_STATE_RUNNING             2
#define OS_THREAD_STATE_READY               3
#define OS_THREAD_STATE_PEND                4
#define OS_THREAD_STATE_PEND_TIMEOUT        5
#define OS_THREAD_STATE_DELAY               6
#define OS_THREAD_STATE_DELAY_TIMEOUT       7
#define OS_THREAD_STATE_YIELD               8
#define OS_THREAD_STATE_DIED                9

typedef struct os_thread_s {
    void* sp; /* stack pointer */
    char name[OS_NAME_MAX_SIZE];
    void* start_entry;
    void* parameter;
    uint8_t * stack_address;
    os_size_t stack_size;
    void (*exit_entry)(struct os_thread_s*);
    os_tick_t init_tick;
    os_tick_t remain_ticks;
    os_priority_t init_priority;
    os_priority_t current_priority;
    os_list_node_t ready_node;
    os_list_node_t pend_node;
    os_timer_t timer;
    int state;
    int flag;
    os_err_t error;
}os_thread_t;

typedef void (*os_thread_entry_t)(void* p);
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
                        );

os_err_t os_thread_startup(os_thread_t* thread);

os_thread_t * os_thread_self(void);

void os_thread_yield(void);

void os_thread_delay(os_tick_t ticks);

void os_thread_mdelay(os_uint_t ms);

#endif /* INCLUDED_OS_THREAD_H */
