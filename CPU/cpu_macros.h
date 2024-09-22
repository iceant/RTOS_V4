#ifndef INCLUDED_CPU_MACROS_H
#define INCLUDED_CPU_MACROS_H

/* -------------------------------------------------------------------------------------------------------------- */
/*  */
#ifndef INCLUDED_CPU_TYPES_H
#include <cpu_types.h>
#endif /*INCLUDED_CPU_TYPES_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* UTILS */

#define CPU_REG(A) (*(volatile cpu_uint_t*)(A))


#define CPU_BIT(x)              (1<<(x))
#define CPU_BIT_SET(x,p)        ((x)|(1<<(p)))
#define CPU_BIT_CLEAR(x,p)      ((x)&(~(1<<(p))))
#define CPU_BIT_GET(x,p)        (((x)>>(p))&1)
#define CPU_BIT_TOGGLE(x,p)     ((x)^(1<<(p)))



#endif /* INCLUDED_CPU_MACROS_H */
