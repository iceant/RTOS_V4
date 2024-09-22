#ifndef INCLUDED_OS_SCHEDULER_H
#define INCLUDED_OS_SCHEDULER_H

/* -------------------------------------------------------------------------------------------------------------- */
/* DEPENDENCIES */

#ifndef INCLUDED_OS_TYPES_H
#include <os_types.h>
#endif /*INCLUDED_OS_TYPES_H*/

#ifndef INCLUDED_OS_ERROR_H
#include <os_error.h>
#endif /*INCLUDED_OS_ERROR_H*/

#ifndef INCLUDED_OS_THREAD_H
#include <os_thread.h>
#endif /*INCLUDED_OS_THREAD_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* EXTERNAL VARIABLES */
extern volatile os_thread_t * os_scheduler_current_thread_p;

/* -------------------------------------------------------------------------------------------------------------- */
/*  */

os_err_t os_scheduler_init(void);

os_err_t os_scheduler_startup(void);

volatile os_thread_t* os_scheduler_current_thread(void);

void os_scheduler_disable(void);

void os_scheduler_enable(void);

/* -------------------------------------------------------------------------------------------------------------- */
/* ERRORS */

#define OS_SCHEDULER_ERR_INT_NEST                   0x2001
#define OS_SCHEDULER_ERR_DISABLED                   0x2002
#define OS_SCHEDULER_ERR_NOTHREAD                   0x2003
#define OS_SCHEDULER_ERR_SAME_AS_CURRENT_THREAD     0x2004
#define OS_SCHEDULER_ERR_WIP                        0x2005
#define OS_SCHEDULER_ERR_RETRY                      0x2006
#define OS_SCHEDULER_ERR_NOT_START                  0x2007
#define OS_SCHEDULER_ERR_CURRENT_THREAD_RUNNING     0x2008

#define OS_SCHEDULER_FLAG_NONE                      0
#define OS_SCHEDULER_FLAG_WIP                       1

/* -------------------------------------------------------------------------------------------------------------- */
/* METHOS */
os_err_t os_scheduler_init(void);

os_err_t os_scheduler_startup(void);

os_err_t os_scheduler_schedule(void);

os_bool_t os_scheduler_is_need_schedule(void);

void os_scheduler_set_need_schedule(int flag);

os_err_t os_scheduler_systick(void);

os_err_t os_scheduler_resume(os_thread_t* thread);

os_err_t os_scheduler_delay(os_thread_t* thread, os_tick_t ticks);

os_err_t os_scheduler_delay_no_schedule(os_thread_t* thread, os_tick_t ticks);

os_err_t  os_scheduler_yield(os_thread_t* thread);

#endif /* INCLUDED_OS_SCHEDULER_H */
