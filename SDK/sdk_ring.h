#ifndef INCLUDED_SDK_RING_H
#define INCLUDED_SDK_RING_H


#ifndef INCLUDED_SDK_TYPES_H
#include <sdk_types.h>
#endif /*INCLUDED_SDK_TYPES_H*/

#ifndef INCLUDED_SDK_ERROR_H
#include <sdk_error.h>
#endif /*INCLUDED_SDK_ERROR_H*/


/* -------------------------------------------------------------------------------------------------------------- */
/* TYPES */


typedef struct sdk_ring_s{
    uint8_t *   array;          /* Memory to hold array of objects, array size = capacity * object_size */
    size_t   capacity;       /* How many objects */
    size_t   object_size;    /* Object Size */
    size_t   read_idx;
    size_t   write_idx;
}sdk_ring_t;

////////////////////////////////////////////////////////////////////////////////
////
void sdk_ring_init(sdk_ring_t * ring, void* array, size_t element_count, size_t element_size);

sdk_err_t sdk_ring_put(sdk_ring_t *ring, void* object);

sdk_err_t sdk_ring_get(sdk_ring_t * ring, void* object);

size_t sdk_ring_used(sdk_ring_t * ring);

sdk_err_t sdk_ring_read(sdk_ring_t * ring, size_t offset, void* object);

void sdk_ring_reset(sdk_ring_t * ring);

////////////////////////////////////////////////////////////////////////////////
//// Only used in one thread context

void* sdk_ring_peek(sdk_ring_t * ring, size_t offset /*0<= offset <used*/);

void* sdk_ring_pop(sdk_ring_t * ring);

////////////////////////////////////////////////////////////////////////////////
////
void* sdk_ring_get_write_slot(sdk_ring_t* ring);



#endif /*INCLUDED_SDK_RING_H*/
