#ifndef INCLUDED_OS_TIMER_H
#define INCLUDED_OS_TIMER_H

#ifndef INCLUDED_OS_TYPES_H
#include <os_types.h>
#endif /*INCLUDED_OS_TYPES_H*/

#ifndef INCLUDED_OS_LIST_H
#include <os_list.h>
#endif /*INCLUDED_OS_LIST_H*/

#ifndef INCLUDED_OS_TICK_H
#include <os_tick.h>
#endif /*INCLUDED_OS_TICK_H*/

#ifndef INCLUDED_OS_ERROR_H
#include <os_error.h>
#endif /*INCLUDED_OS_ERROR_H*/


/* -------------------------------------------------------------------------------------------------------------- */
/* TYPES */
typedef struct os_timer_s os_timer_t;

typedef void (*os_timer_function_t)(os_timer_t*);

struct os_timer_s{
    os_list_node_t wait_node;
    os_tick_t period_tick;
    os_tick_t expire_tick;
    os_timer_function_t timer_function;
    void* userdata;
    int flag;
};

/* -------------------------------------------------------------------------------------------------------------- */
/* FLAGS */

#define OS_TIMER_FLAG_ONCE      0
#define OS_TIMER_FLAG_REPEAT    1

/* -------------------------------------------------------------------------------------------------------------- */
/* METHODS */

os_err_t os_timer_init(os_timer_t* timer, os_timer_function_t fn, void* userdata, os_tick_t period_ticks, int flag);


#endif /* INCLUDED_OS_TIMER_H */
