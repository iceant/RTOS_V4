#include <sdk_memory.h>

#if (RTOS_SDK_ENABLE_RTOS)
#include <os_memory.h>

void* sdk_memory_alloc(sdk_size_t bytes, const char* file, int line)
{
    return os_memory_alloc(bytes);
}

void* sdk_memory_realloc(void* p, sdk_size_t bytes, const char* file, int line){
    return os_memory_realloc(p, bytes);
}

void* sdk_memory_calloc(sdk_size_t count, sdk_size_t bytes, const char* file, int line){
    return os_memory_calloc(count, bytes);
}

void sdk_memory_free(void* p, const char* file, int line){
    if(p){
        os_memory_free(p);
    }
}
#else
#include <stdlib.h>

void* sdk_memory_alloc(sdk_size_t bytes, const char* file, int line)
{
    return malloc(bytes);
}

void* sdk_memory_realloc(void* p, sdk_size_t bytes, const char* file, int line){
    return realloc(p, bytes);
}

void* sdk_memory_calloc(sdk_size_t count, sdk_size_t bytes, const char* file, int line){
    return calloc(count, bytes);
}

void sdk_memory_free(void* p, const char* file, int line){
    if(p){
        free(p);
    }
}
#endif

