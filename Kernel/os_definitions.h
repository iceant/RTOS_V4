#ifndef INCLUDED_OS_DEFINITIONS_H
#define INCLUDED_OS_DEFINITIONS_H

#ifndef INCLUDED_CPU_H
#include <cpu.h>
#endif /*INCLUDED_CPU_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* DEFINITIONS */

#ifndef OS_MEMORY_USE_TLSF
    #define OS_MEMORY_USE_TLSF 1
#endif

#ifndef OS_MEMORY_POOL_SIZE
    #define OS_MEMORY_POOL_SIZE (5*1024)
#endif

#ifndef OS_NAME_MAX_SIZE
    #define OS_NAME_MAX_SIZE 16
#endif

#ifndef OS_TICK_PER_SECOND
    #define OS_TICK_PER_SECOND 1000u
#endif

#ifndef OS_PRIORITY_MAX
    #define OS_PRIORITY_MAX 32
#endif


#ifndef OS_INT_CPU_BITS
    #define OS_INT_CPU_BITS CPU_BITS
#endif

#ifndef OS_THREAD_IDLE_PRIORITY
    #define OS_THREAD_IDLE_PRIORITY (OS_PRIORITY_MAX-1)
#endif

#ifndef OS_THREAD_IDLE_STACK_SIZE
    #define OS_THREAD_IDLE_STACK_SIZE 256
#endif

#ifndef OS_THREAD_IDLE_TICKS
    #define OS_THREAD_IDLE_TICKS 5
#endif

#ifndef OS_ENABLE_STACK_OVERFLOW_CHECK
    #define OS_ENABLE_STACK_OVERFLOW_CHECK 1
#endif

#ifndef OS_PRINTF_BUFFER_SIZE
    #define OS_PRINTF_BUFFER_SIZE 1024
#endif

#endif /* INCLUDED_OS_DEFINITIONS_H */
