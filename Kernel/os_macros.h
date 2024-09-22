#ifndef INCLUDED_OS_MACROS_H
#define INCLUDED_OS_MACROS_H

/* -------------------------------------------------------------------------------------------------------------- */
/* TYPES */

#ifndef INCLUDED_OS_TYPES_H
#include <os_types.h>
#endif /*INCLUDED_OS_TYPES_H*/


/* -------------------------------------------------------------------------------------------------------------- */
/*  */

#define OS_MIN(a, b)                ((a)>(b)?(b):(a))
#define OS_MAX(a, b)                ((a)>(b)?(a):(b))

#define OS_ABS(x)                   (((x) <  0) ? -(x) : (x))

#define OS_ARRAY_SIZE(a)            (sizeof(a) / sizeof((a)[0]))
#define OS_IS_ARRAY(a)              ((void *)&a == (void *)a)
#define OS_ARRAY_SET(d, n, v) \
do{ os_size_t i_, n_;         \
    for ( n_ = (n), i_ = 0; n_ > 0; --n_, ++i_) \
        (d)[i_] = (v);        \
    }                         \
while(0)

#define OS_ARRAY_ZERO(d, n)         OS_ARRAY_SET(d, n, 0)

#define OS_BIT(x)                   (1<<(x))
#define OS_BIT_SET(x,p)             ((x)|(1<<(p)))
#define OS_BIT_CLEAR(x,p)           ((x)&(~(1<<(p))))
#define OS_BIT_GET(x,p)             (((x)>>(p))&1)
#define OS_BIT_TOGGLE(x,p)          ((x)^(1<<(p)))

#define OS_FLOORB(x, align)         ((x) & ~((align) - 1))
#define OS_CEILB(x, align)          (((x) + ((align) - 1)) & ~((align) - 1))

#define OS_ONCE2(stmts, i)     \
{                              \
    static int i = 1;          \
    if(i){                     \
        stmts                  \
        i = 0;                 \
    }                          \
}

#define OS_ONCE(stmts)         OS_ONCE2(stmts, __os_once_var_##__COUNTER__)

#endif /* INCLUDED_OS_MACROS_H */
