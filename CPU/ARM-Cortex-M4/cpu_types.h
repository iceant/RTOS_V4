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

/* -------------------------------------------------------------------------------------------------------------- */
/* TYPES */

typedef int32_t     cpu_int_t;
typedef uint32_t    cpu_uint_t;
typedef int32_t     cpu_intptr_t;
typedef uint32_t    cpu_uintptr_t;


#endif /* INCLUDED_CPU_TYPES_H */
