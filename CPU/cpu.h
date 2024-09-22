#ifndef INCLUDED_CPU_H
#define INCLUDED_CPU_H

/* -------------------------------------------------------------------------------------------------------------- */
/* COMPILER */
#ifndef INCLUDED_C_COMPILER_H
#include <c_compiler.h>
#endif /*INCLUDED_C_COMPILER_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* CPU OPTIONS */
#ifndef INCLUDED_CPU_OPTIONS_H
#include <cpu_options.h>
#endif /*INCLUDED_CPU_OPTIONS_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* CPU TYPES */
#ifndef INCLUDED_CPU_TYPES_H
#include <cpu_types.h>
#endif /*INCLUDED_CPU_TYPES_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* CPU STACK */
#ifndef INCLUDED_CPU_STACK_H
#include <cpu_stack.h>
#endif /*INCLUDED_CPU_STACK_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* CPU LOCKS */
#ifndef INCLUDED_CPU_LOCK_H
#include <cpu_lock.h>
#endif /*INCLUDED_CPU_LOCK_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* CPU FUNCTIONS */
#ifndef INCLUDED_CPU_FUNCTIONS_H
#include <cpu_functions.h>
#endif /*INCLUDED_CPU_FUNCTIONS_H*/


/* -------------------------------------------------------------------------------------------------------------- */
/* MACROS */
#ifndef INCLUDED_CPU_MACROS_H
#include <cpu_macros.h>
#endif /*INCLUDED_CPU_MACROS_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* CPU OPTIONAL FEATURES */
#if (CPU_SPINLOCK_ENABLE==1)
    #ifndef INCLUDED_CPU_SPINLOCK_H
    #include <cpu_spinlock.h>
    #endif /*INCLUDED_CPU_SPINLOCK_H*/
#endif

#if (CPU_ATOMIC_ENABLE==1)
    #ifndef INCLUDED_CPU_ATOMIC_H
    #include <cpu_atomic.h>
    #endif /*INCLUDED_CPU_ATOMIC_H*/
#endif

#ifndef INCLUDED_CPU_SPECIAL_H
#include <cpu_special.h>
#endif /*INCLUDED_CPU_SPECIAL_H*/


/* -------------------------------------------------------------------------------------------------------------- */
/* INIT */

#ifndef INCLUDED_CPU_INIT_H
#include <cpu_init.h>
#endif /*INCLUDED_CPU_INIT_H*/


#endif /* INCLUDED_CPU_H */

