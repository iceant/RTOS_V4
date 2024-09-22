#ifndef INCLUDED_SDK_MEMORY_H
#define INCLUDED_SDK_MEMORY_H

#ifndef INCLUDED_SDK_ERROR_H
#include <sdk_error.h>
#endif /*INCLUDED_SDK_ERROR_H*/

#ifndef INCLUDED_STRING_H
#define INCLUDED_STRING_H
#include <string.h>
#endif /*INCLUDED_STRING_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* METHDOS */

void* sdk_memory_alloc(sdk_size_t bytes, const char* file, int line);
void* sdk_memory_realloc(void* p, sdk_size_t bytes, const char* file, int line);
void* sdk_memory_calloc(sdk_size_t count, sdk_size_t bytes, const char* file, int line);
void sdk_memory_free(void* p, const char* file, int line);

/* -------------------------------------------------------------------------------------------------------------- */
/* UTILS */

#define SDK_ALLOC(x) sdk_memory_alloc((x), __FILE__, __LINE__)
#define SDK_CALLOC(n, x) sdk_memory_calloc((n), (x), __FILE__, __LINE__)
#define SDK_REALLOC(p, x) sdk_memory_realloc((p), (x), __FILE__, __LINE__)
#define SDK_RESIZE(p, x) (p)=SDK_REALLOC(p, x)
#define SDK_FREE(p) (sdk_memory_free((p), __FILE__, __LINE__), (p)=0)

#define SDK_NEW(p) (p)=SDK_ALLOC(sizeof(*(p)))
#define SDK_NEW0(p) (p)=SDK_CALLOC(1, sizeof(*(p)))

#endif /* INCLUDED_SDK_MEMORY_H */
