#ifndef INCLUDED_SDK_VECTOR_H
#define INCLUDED_SDK_VECTOR_H

/* -------------------------------------------------------------------------------------------------------------- */
/* DEPENDENCIES */

#ifndef INCLUDED_SDK_ERROR_H
#include <sdk_error.h>
#endif /*INCLUDED_SDK_ERROR_H*/


/* -------------------------------------------------------------------------------------------------------------- */
/* TYPES */

typedef struct sdk_vector_s{
    void** items;
    sdk_size_t capacity;
    sdk_size_t size;
}sdk_vector_t;

/* -------------------------------------------------------------------------------------------------------------- */
/* METHODS */
sdk_err_t sdk_vector_init(sdk_vector_t* vector, sdk_size_t capacity);

void sdk_vector_destroy(sdk_vector_t* vector);

sdk_err_t sdk_vector_append(sdk_vector_t* vector, void* item);

C_STATIC_FORCE_INLINE sdk_size_t sdk_vector_size(sdk_vector_t* vector){
    return vector->size;
}

C_STATIC_FORCE_INLINE sdk_size_t sdk_vector_capacity(sdk_vector_t* vector){
    return vector->capacity;
}

sdk_err_t sdk_vector_resize(sdk_vector_t* vector, sdk_size_t capacity);

void* sdk_vector_get(sdk_vector_t* vector, sdk_size_t idx);

sdk_err_t sdk_vector_set(sdk_vector_t* vector, sdk_size_t idx, void* item);

sdk_err_t sdk_vector_remove(sdk_vector_t* vector, sdk_size_t idx);

sdk_err_t sdk_vector_resize_remove(sdk_vector_t* vector, sdk_size_t idx);

sdk_err_t sdk_vector_resize_append(sdk_vector_t* vector, void* item);

#endif /* INCLUDED_SDK_VECTOR_H */
