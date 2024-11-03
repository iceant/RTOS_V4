#ifndef INCLUDED_CPU_MACROS_H
#define INCLUDED_CPU_MACROS_H

/* -------------------------------------------------------------------------------------------------------------- */
/*  */
#ifndef INCLUDED_CPU_TYPES_H
#include <cpu_types.h>
#endif /*INCLUDED_CPU_TYPES_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* UTILS */

#define CPU_REG(A)              (*(volatile cpu_uint_t*)(A))

#define CPU_REG8(A)             (*(volatile uint8_t*)(A))
#define CPU_REG16(A)            (*(volatile uint16_t*)(A))
#define CPU_REG32(A)            (*(volatile uint32_t*)(A))

#define CPU_BIT(x)              (1<<(x))
#define CPU_BIT_SET(x,p)        ((x)|(1<<(p)))
#define CPU_BIT_CLEAR(x,p)      ((x)&(~(1<<(p))))
#define CPU_BIT_GET(x,p)        (((x)>>(p))&1)
#define CPU_BIT_TOGGLE(x,p)     ((x)^(1<<(p)))

#define CPU_BITS_IN(start, end)          ((CPU_UINT_MAX << (start)) & (CPU_UINT_MAX >> ((CPU_BITS-1) - (cpu_uint_t)(end))))
#define CPU_BITS_GET(regval, start, end)       (((regval) & CPU_BITS_IN((start),(end))) >> (start))

#endif /* INCLUDED_CPU_MACROS_H */
