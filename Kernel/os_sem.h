#ifndef INCLUDED_OS_SEM_H
#define INCLUDED_OS_SEM_H
/* -------------------------------------------------------------------------------------------------------------- */
/*  */

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

#ifndef INCLUDED_OS_WAITOBJECT_H
#include <os_waitobject.h>
#endif /*INCLUDED_OS_WAITOBJECT_H*/

#ifndef INCLUDED_CPU_SPINLOCK_H
#include <cpu_spinlock.h>
#endif /*INCLUDED_CPU_SPINLOCK_H*/


/* -------------------------------------------------------------------------------------------------------------- */
/* TYPES */

typedef struct os_sem_s{
    os_waitobject_t wait_object;
    os_uint_t value;
    char name[OS_NAME_MAX_SIZE];
}os_sem_t;

/* -------------------------------------------------------------------------------------------------------------- */
/* FLAG */

#define OS_SEM_FLAG_FIFO OS_WAIT_FLAG_FIFO
#define OS_SEM_FLAG_PRIO OS_WAIT_FLAG_PRIO

/* -------------------------------------------------------------------------------------------------------------- */
/* METHODS */

os_err_t os_sem_init(os_sem_t* sem, const char* name, os_uint_t init_value, int flag);

/*
 * wait_for_ticks
 *  - 0                 : return OS_ERR_TIMEOUT
 *  - OS_WAIT_FOREVER   : wait until notify
 */
os_err_t os_sem_take(os_sem_t * sem, os_tick_t wait_for_ticks);

os_err_t os_sem_release(os_sem_t* sem);

#endif /* INCLUDED_OS_SEM_H */
