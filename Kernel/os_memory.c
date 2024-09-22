#include <os_memory.h>
#if defined(OS_MEMORY_USE_TLSF)

#include <tlsf.h>

static uint8_t os_memory__pool[OS_MEMORY_POOL_SIZE];

void os_memory_init(void){
    init_memory_pool(OS_MEMORY_POOL_SIZE, os_memory__pool);
}

void os_memory_destroy(void){
    destroy_memory_pool(os_memory__pool);
}


void* os_memory_alloc(os_size_t nBytes){
    return tlsf_malloc(nBytes);
}

void* os_memory_calloc(os_size_t nCount, os_size_t nBytes){
    return tlsf_calloc(nCount, nBytes);
}

void* os_memory_realloc(void* ptr, os_size_t nBytes){
    return tlsf_realloc(ptr, nBytes);
}

void os_memory_free(void* p){
    if(p){
        tlsf_free(p);
    }
}

#else

void os_memory_init(void){

}

void os_memory_destroy(void){

}


void* os_memory_alloc(os_size_t nBytes){
    return 0;
}

void* os_memory_calloc(os_size_t nCount, os_size_t nBytes){
    return 0;
}

void* os_memory_realloc(void* ptr, os_size_t nBytes){
    return 0;
}

void os_memory_free(void* p){

}
#endif

