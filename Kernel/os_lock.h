#ifndef INCLUDED_OS_LOCK_H
#define INCLUDED_OS_LOCK_H

#ifndef INCLUDED_OS_TYPES_H
#include <os_types.h>
#endif /*INCLUDED_OS_TYPES_H*/

#ifndef INCLUDED_OS_ERROR_H
#include <os_error.h>
#endif /*INCLUDED_OS_ERROR_H*/

#ifndef INCLUDED_CPU_H
#include <cpu.h>
#endif /*INCLUDED_CPU_H*/


/* -------------------------------------------------------------------------------------------------------------- */
/* TYPES */

typedef cpu_lock_t os_lock_t;

/* -------------------------------------------------------------------------------------------------------------- */
/*  */

C_STATIC_FORCE_INLINE void os_lock_init(os_lock_t* lock){
    cpu_lock_init(lock);
}

C_STATIC_FORCE_INLINE void os_lock_lock(os_lock_t* lock){
    cpu_lock_lock(lock);
}

C_STATIC_FORCE_INLINE void os_lock_unlock(os_lock_t* lock){
    cpu_lock_unlock(lock);
}


#endif /* INCLUDED_OS_LOCK_H */
