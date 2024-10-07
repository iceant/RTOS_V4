#include <sdk_vector.h>
#include <sdk_memory.h>

#define ELEMENT_SIZE sizeof(void*)

sdk_err_t sdk_vector_init(sdk_vector_t* vector, sdk_size_t capacity){
    vector->capacity = capacity;
    vector->size = 0;
    if(capacity>0){
        vector->items = SDK_ALLOC(ELEMENT_SIZE * capacity);
        if(!vector->items){
            return SDK_ERR_NOMEM;
        }
    }else{
        vector->items = 0;
    }
    return SDK_ERR_OK;
}


void sdk_vector_destroy(sdk_vector_t* vector){
    SDK_FREE(vector->items);
    vector->size =0;
}

sdk_err_t sdk_vector_append(sdk_vector_t* vector, void* item){
    if(vector->size>=vector->capacity){
        return SDK_ERR_FULL;
    }
    vector->items[vector->size++] = item;
    return SDK_ERR_OK;
}

sdk_err_t sdk_vector_resize_append(sdk_vector_t* vector, void* item){
    sdk_err_t err;
    if(vector->size>=vector->capacity){
        err = sdk_vector_resize(vector, (vector->capacity==0)?1:vector->capacity*2);
        if(err!=SDK_ERR_OK){
            return err;
        }
    }
    vector->items[vector->size++] = item;
    return SDK_ERR_OK;
}

sdk_err_t sdk_vector_resize(sdk_vector_t* vector, sdk_size_t capacity){
    if(capacity==0){
        SDK_FREE(vector->items);
        vector->size = 0;
    }else if(capacity > vector->capacity){
        void** items = SDK_ALLOC(ELEMENT_SIZE * capacity);
        if(!items){
            return SDK_ERR_NOMEM;
        }
        memcpy(items, vector->items, ELEMENT_SIZE * vector->size);
        SDK_FREE(vector->items);
        vector->items = items;
    }else if(capacity < vector->capacity){
        SDK_RESIZE(vector->items, capacity * ELEMENT_SIZE);
        if(!vector->items){
            return SDK_ERR_NOMEM;
        }
        if(capacity <= vector->size){
            vector->size = capacity;
        }
    }
    
    vector->capacity = capacity;
    return SDK_ERR_OK;
}

void* sdk_vector_get(sdk_vector_t* vector, sdk_size_t idx){
    if(idx>=vector->size){
        return 0;
    }
    return vector->items[idx];
}

sdk_err_t sdk_vector_set(sdk_vector_t* vector, sdk_size_t idx, void* item){
    if(idx>=vector->size){
        return SDK_ERR_PARAM;
    }
    vector->items[idx] = item;
    return SDK_ERR_OK;
}

sdk_err_t sdk_vector_remove(sdk_vector_t* vector, sdk_size_t idx){
    if(idx>=vector->size){
        return SDK_ERR_PARAM;
    }
    sdk_size_t i;
    for(i=idx; i<(vector->size-1); i++){
        vector->items[i] = vector->items[i+1];
    }
    vector->items[i] = 0;
    vector->size--;
    
    return SDK_ERR_OK;
}

sdk_err_t sdk_vector_resize_remove(sdk_vector_t* vector, sdk_size_t idx){
    if(idx>=vector->size){
        return SDK_ERR_PARAM;
    }
    sdk_size_t i;
    for(i=idx; i<(vector->size-1); i++){
        vector->items[i] = vector->items[i+1];
    }
    vector->items[i] = 0;
    vector->size--;
    
    if(vector->size <= (vector->capacity/4)){
        sdk_err_t  err = sdk_vector_resize(vector, vector->capacity/2);
        if(err!=SDK_ERR_OK){
            return err;
        }
    }
    
    return SDK_ERR_OK;
}