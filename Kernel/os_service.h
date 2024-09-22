#ifndef INCLUDED_OS_SERVICE_H
#define INCLUDED_OS_SERVICE_H

#ifndef INCLUDED_CPU_H
#include <cpu.h>
#endif /*INCLUDED_CPU_H*/

#ifndef INCLUDED_OS_ERROR_H
#include <os_error.h>
#endif /*INCLUDED_OS_ERROR_H*/

#ifndef INCLUDED_OS_THREAD_H
#include <os_thread.h>
#endif /*INCLUDED_OS_THREAD_H*/

#ifndef INCLUDED_OS_WAITOBJECT_H
#include <os_waitobject.h>
#endif /*INCLUDED_OS_WAITOBJECT_H*/


/* -------------------------------------------------------------------------------------------------------------- */
/* METHODS */

void os_service_init(void);

os_err_t os_service_reboot(void);

os_err_t os_service_schedule(void);

os_err_t os_service_resume(os_thread_t* thread);

os_err_t os_service_yield(os_thread_t* thread);

os_err_t os_service_systick(void);

os_err_t os_service_delay(os_thread_t* thread, os_tick_t ticks);

os_err_t os_service_wait(os_waitobject_t * wait_object, os_thread_t * thread, os_tick_t ticks);

os_err_t os_service_notify(os_waitobject_t * wait_object);

os_err_t os_service_notify_all(os_waitobject_t * wait_object);

#endif /* INCLUDED_OS_SERVICE_H */
