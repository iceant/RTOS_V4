#ifndef INCLUDED_OS_MEMORY_H
#define INCLUDED_OS_MEMORY_H

#ifndef INCLUDED_OS_TYPES_H
#include <os_types.h>
#endif /*INCLUDED_OS_TYPES_H*/

#ifndef INCLUDED_STRING_H
#define INCLUDED_STRING_H
#include <string.h>
#endif /*INCLUDED_STRING_H*/



/* -------------------------------------------------------------------------------------------------------------- */
/* METHODS */

void os_memory_init(void);

void os_memory_destroy(void);

void* os_memory_alloc(os_size_t nBytes);

void* os_memory_calloc(os_size_t nCount, os_size_t nBytes);

void* os_memory_realloc(void* ptr, os_size_t nBytes);

void os_memory_free(void* p);

/* -------------------------------------------------------------------------------------------------------------- */
/* UTILS */

#define OS_ALLOC(n) os_memory_alloc((n))
#define OS_CALLOC(x, n) os_memory_calloc((x), (n))
#define OS_REALLOC(p, n) os_memory_realloc((p), (n))
#define OS_RESIZE(p, n) (p)=os_memory_realloc((p), (n))
#define OS_FREE(p) ((os_memory_free((p))), (p)=0)

#define OS_NEW(p) (p)=OS_ALLOC(sizeof(*(p)))
#define OS_NEW0(p) (p)=OS_CALLOC(1, sizeof(*(p)))

#endif /* INCLUDED_OS_MEMORY_H */
