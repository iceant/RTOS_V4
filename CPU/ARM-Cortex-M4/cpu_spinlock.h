#ifndef INCLUDED_CPU_SPINLOCK_H
#define INCLUDED_CPU_SPINLOCK_H

/* -------------------------------------------------------------------------------------------------------------- */
/* DEPENDENCIES */

#ifndef INCLUDED_CPU_FUNCTIONS_H
#include <cpu_functions.h>
#endif /*INCLUDED_CPU_FUNCTIONS_H*/

#ifndef INCLUDED_C_COMPILER_H
#include <c_compiler.h>
#endif /*INCLUDED_C_COMPILER_H*/

#ifndef INCLUDED_CPU_LOCK_H
#include <cpu_lock.h>
#endif /*INCLUDED_CPU_LOCK_H*/



/* -------------------------------------------------------------------------------------------------------------- */
/* TYPES */
typedef volatile cpu_int_t cpu_spinlock_t;

/* -------------------------------------------------------------------------------------------------------------- */
/* METHODS */

C_STATIC_FORCE_INLINE void cpu_spinlock_init(cpu_spinlock_t* lock){
    *lock = 0;
}

C_STATIC_FORCE_INLINE cpu_int_t cpu_spinlock_lock(cpu_spinlock_t* lock){
    cpu_uint_t status;
    do{
        while(cpu_ldrexw((volatile cpu_uint_t*)lock)!=0);
        status = cpu_strexw(1, (volatile cpu_uint_t*)lock);
    }while(status!=0);
    cpu_dmb();
    return status;
}

C_STATIC_FORCE_INLINE void cpu_spinlock_unlock(cpu_spinlock_t* lock){
    cpu_dmb();
    *lock = 0;
}

C_STATIC_FORCE_INLINE cpu_int_t cpu_spinlock_try_lock(cpu_spinlock_t* lock){
    cpu_int_t status;
    if(cpu_ldrexw((volatile cpu_uint_t*)lock)!=0){
        return -1;
    }
    status = cpu_strexw(1, (volatile cpu_uint_t*)lock);
    cpu_dmb();
    return status;
}

/* -------------------------------------------------------------------------------------------------------------- */
/* 当在应用和中断中都可能使用spinlock时，需要在应用中使用下面的方法 */

C_STATIC_FORCE_INLINE cpu_uint_t cpu_spinlock_irq_save(cpu_spinlock_t* lock, cpu_uint_t* saved_irq_lock){
    cpu_lock_lock(saved_irq_lock);
    return cpu_spinlock_lock(lock);
}

C_STATIC_FORCE_INLINE void cpu_spinlock_irq_restore(cpu_spinlock_t* lock, cpu_uint_t* saved_irq_lock){
    cpu_spinlock_unlock(lock);
    cpu_lock_unlock(saved_irq_lock);
}


#endif /* INCLUDED_CPU_SPINLOCK_H */
