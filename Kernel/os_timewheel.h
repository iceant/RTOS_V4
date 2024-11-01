#ifndef INCLUDED_OS_TIMEWHEEL_H
#define INCLUDED_OS_TIMEWHEEL_H

#ifndef INCLUDED_OS_TYPES_H
#include <os_types.h>
#endif /*INCLUDED_OS_TYPES_H*/

#ifndef INCLUDED_OS_ERROR_H
#include <os_error.h>
#endif /*INCLUDED_OS_ERROR_H*/

#ifndef INCLUDED_OS_TIMER_H
#include <os_timer.h>
#endif /*INCLUDED_OS_TIMER_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* RESULT */

#define OS_TIMEWHEEL_ERR_NEED_SCHEDULE 0x1001

/* -------------------------------------------------------------------------------------------------------------- */
/* FUNCTIONS */
os_err_t os_timewheel_init(void);

os_err_t os_timewheel_add_timer(os_timer_t* timer, os_timer_function_t fn, void* userdata, os_tick_t ticks, int flag);

os_err_t os_timewheel_tick(void);

os_tick_t os_timewheel_get_tick(void);

void os_timewheel_remove_timer(os_timer_t * timer);

#endif /* INCLUDED_OS_TIMEWHEEL_H */
