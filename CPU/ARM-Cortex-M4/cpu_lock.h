#ifndef INCLUDED_CPU_LOCK_H
#define INCLUDED_CPU_LOCK_H

#ifndef INCLUDED_CPU_FUNCTIONS_H
#include <cpu_functions.h>
#endif /*INCLUDED_CPU_FUNCTIONS_H*/

#ifndef INCLUDED_CPU_OPTIONS_H
#include <cpu_options.h>
#endif /*INCLUDED_CPU_OPTIONS_H*/


/* -------------------------------------------------------------------------------------------------------------- */
/*  */

typedef volatile cpu_uint_t cpu_lock_t;


/* -------------------------------------------------------------------------------------------------------------- */
/* METHODS */

C_STATIC_FORCE_INLINE void cpu_lock_init(cpu_lock_t* lock){
    *lock = 0;
}

C_STATIC_FORCE_INLINE void cpu_lock_lock(cpu_lock_t* lock){
    #if (CPU_LOCK_USE_BASEPRI==1)
        cpu_uint_t current = cpu_get_basepri();
        cpu_set_basepri(CPU_LOCK_BASEPRI_PRIO);
        *lock = current;
    #else
        cpu_uint_t current = cpu_get_primask();
        cpu_disable_irq();
        *lock = current;
    #endif
}

C_STATIC_FORCE_INLINE void cpu_lock_unlock(cpu_lock_t* lock){
    #if (CPU_LOCK_USE_BASEPRI==1)
        cpu_set_basepri(*lock);
    #else
        cpu_set_primask(*lock);
    #endif
}



#endif /* INCLUDED_CPU_LOCK_H */
