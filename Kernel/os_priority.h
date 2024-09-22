#ifndef INCLUDED_OS_PRIORITY_H
#define INCLUDED_OS_PRIORITY_H

#ifndef INCLUDED_OS_TYPES_H
#include <os_types.h>
#endif /*INCLUDED_OS_TYPES_H*/

#ifndef INCLUDED_OS_ERROR_H
#include <os_error.h>
#endif /*INCLUDED_OS_ERROR_H*/


/* -------------------------------------------------------------------------------------------------------------- */
/* TYPES */

typedef os_uint_t os_priority_t;

#define OS_PRIORITY_CMP_EQ      0
#define OS_PRIORITY_CMP_HIGH    1
#define OS_PRIORITY_CMP_LOW     (-1)

/* -------------------------------------------------------------------------------------------------------------- */
/* METHDO */
os_err_t os_priority_init(void);

os_priority_t os_priority_highest(void);

void os_priority_mark(os_priority_t priority);

void os_priority_unmark(os_priority_t priority);

C_STATIC_FORCE_INLINE int os_priority_cmp(os_priority_t a, os_priority_t b){
    if(a==b) return 0;
    return a>b?-1:1;
}

#endif /* INCLUDED_OS_PRIORITY_H */
