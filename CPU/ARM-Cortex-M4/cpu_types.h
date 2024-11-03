#ifndef INCLUDED_CPU_TYPES_H
#define INCLUDED_CPU_TYPES_H

/* -------------------------------------------------------------------------------------------------------------- */
/* DEPENDENCIES */
#ifndef INCLUDED_STDINT_H
#define INCLUDED_STDINT_H
#include <stdint.h>
#endif /*INCLUDED_STDINT_H*/

#ifndef INCLUDED_STDDEF_H
#define INCLUDED_STDDEF_H
#include <stddef.h>
#endif /*INCLUDED_STDDEF_H*/

#ifndef INCLUDED_CPU_OPTIONS_H
#include <cpu_options.h>
#endif /*INCLUDED_CPU_OPTIONS_H*/


/* -------------------------------------------------------------------------------------------------------------- */
/*  */
#ifndef CPU_SIZEOF_VOID_P
#define CPU_SIZEOF_VOID_P   4
#endif

#ifndef CPU_BITS
#define CPU_BITS            32
#endif

/* -------------------------------------------------------------------------------------------------------------- */
/* TYPES */

typedef int32_t     cpu_int_t;
typedef uint32_t    cpu_uint_t;
typedef int32_t     cpu_intptr_t;
typedef uint32_t    cpu_uintptr_t;

#define CPU_UINT_MAX    UINT32_MAX
#define CPU_INT_MAX     INT32_MAX
#define CPU_INT_MIN     INT32_MIN

#endif /* INCLUDED_CPU_TYPES_H */
