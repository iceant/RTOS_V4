#ifndef INCLUDED_OS_MUTEX_H
#define INCLUDED_OS_MUTEX_H

/* -------------------------------------------------------------------------------------------------------------- */
/*  */

#ifndef INCLUDED_OS_ERROR_H
#include <os_error.h>
#endif /*INCLUDED_OS_ERROR_H*/

#ifndef INCLUDED_OS_WAITOBJECT_H
#include <os_waitobject.h>
#endif /*INCLUDED_OS_WAITOBJECT_H*/

#ifndef INCLUDED_CPU_SPINLOCK_H
#include <cpu_spinlock.h>
#endif /*INCLUDED_CPU_SPINLOCK_H*/


/* -------------------------------------------------------------------------------------------------------------- */
/* TYPES */

typedef struct os_mutex_s{
    os_waitobject_t wait_object;
    cpu_spinlock_t lock;
    os_thread_t * owner;            /* Owner thread */
    os_size_t hold;                 /* Owner hold count */
    int flag;
}os_mutex_t;

/* -------------------------------------------------------------------------------------------------------------- */
/*  */

#define OS_MUTEX_ERR_NOT_OWNER      0x4001
#define OS_MUTEX_ERR_OWNER_HOLD     0x4002

#define OS_MUTEX_FLAG_FIFO          OS_WAIT_FLAG_FIFO
#define OS_MUTEX_FLAG_PRIO          OS_WAIT_FLAG_PRIO

/* -------------------------------------------------------------------------------------------------------------- */
/* METHODS */
os_err_t os_mutex_init(os_mutex_t* mutex, int flag /*OS_MUTEX_FLAG_FIFO | OS_MUTEX_FLAG_PRIO*/);

os_err_t os_mutex_lock(os_mutex_t* mutex, os_tick_t ticks);

os_err_t os_mutex_unlock(os_mutex_t* mutex);

/* -------------------------------------------------------------------------------------------------------------- */
/*  */

#define OS_MUTEX_LOCK(M)            os_mutex_lock((M), OS_WAIT_FOREVER)
#define OS_MUTEX_UNLOCK(M)          os_mutex_unlock((M))


#endif /* INCLUDED_OS_MUTEX_H */
