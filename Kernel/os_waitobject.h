#ifndef INCLUDED_OS_WAITOBJECT_H
#define INCLUDED_OS_WAITOBJECT_H

/* -------------------------------------------------------------------------------------------------------------- */
/* DEPENDENCIES */

#ifndef INCLUDED_OS_TYPES_H
#include <os_types.h>
#endif /*INCLUDED_OS_TYPES_H*/

#ifndef INCLUDED_OS_ERROR_H
#include <os_error.h>
#endif /*INCLUDED_OS_ERROR_H*/

#ifndef INCLUDED_OS_LIST_H
#include <os_list.h>
#endif /*INCLUDED_OS_LIST_H*/

#ifndef INCLUDED_OS_TICK_H
#include <os_tick.h>
#endif /*INCLUDED_OS_TICK_H*/

#ifndef INCLUDED_OS_THREAD_H
#include <os_thread.h>
#endif /*INCLUDED_OS_THREAD_H*/



/* -------------------------------------------------------------------------------------------------------------- */
/* TYPE */

typedef struct os_waitobject_s{
    os_list_t wait_list;
    int flag;
}os_waitobject_t;

/* -------------------------------------------------------------------------------------------------------------- */
/* CONSTANTS */
#define OS_WAIT_FLAG_FIFO 0
#define OS_WAIT_FLAG_PRIO 1

#define OS_WAIT_FOREVER (-1u)

#define OS_WAITOBJECT_ERR_NEED_SCHEDULE 0x3001
/* -------------------------------------------------------------------------------------------------------------- */
/* METHODS */

os_err_t os_waitobject_init(os_waitobject_t* object, int flag);

os_err_t os_waitobject_wait(os_waitobject_t * object, os_thread_t *wait_subject, os_tick_t wait_ticks);

os_err_t os_waitobject_notify_one(os_waitobject_t* object);

os_err_t os_waitobject_notify_all(os_waitobject_t* object);


#endif /* INCLUDED_OS_WAITOBJECT_H */
