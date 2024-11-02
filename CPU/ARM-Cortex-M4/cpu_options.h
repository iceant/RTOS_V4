#ifndef INCLUDED_CPU_OPTIONS_H
#define INCLUDED_CPU_OPTIONS_H

#ifndef CPU_SPINLOCK_ENABLE
    #define CPU_SPINLOCK_ENABLE 1
#endif

#ifndef CPU_ATOMIC_ENABLE
    #define CPU_ATOMIC_ENABLE 1
#endif

#ifndef CPU_LOCK_USE_BASEPRI
    #define CPU_LOCK_USE_BASEPRI 1
#endif

#ifndef CPU_LOCK_BASEPRI_PRIO
    #define CPU_LOCK_BASEPRI_PRIO 0x10
#endif

#ifndef CPU_SIZEOF_VOID_P
    #define CPU_SIZEOF_VOID_P 4
#endif

#ifndef CPU_BITS
    #define CPU_BITS (CPU_SIZEOF_VOID_P * 8)
#endif

#ifndef __FPU_PRESENT
    #define __FPU_PRESENT
#endif

#endif /* INCLUDED_CPU_OPTIONS_H */
