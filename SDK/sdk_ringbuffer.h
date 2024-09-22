#ifndef INCLUDED_SDK_RINGBUFFER_H
#define INCLUDED_SDK_RINGBUFFER_H

/* -------------------------------------------------------------------------------------------------------------- */
/* DEPENDENCIES */

#ifndef INCLUDED_SDK_ERROR_H
#include <sdk_error.h>
#endif /*INCLUDED_SDK_ERROR_H*/



/* -------------------------------------------------------------------------------------------------------------- */
/* TYPES */

typedef struct sdk_ringbuffer_s{
    uint8_t * buffer;
    sdk_size_t buffer_size;
    sdk_size_t write_idx;
    sdk_size_t read_idx;
}sdk_ringbuffer_t;

typedef struct sdk_ringbuffer_pos_s{
    sdk_size_t start;
    sdk_size_t end;
}sdk_ringbuffer_pos_t;

/* -------------------------------------------------------------------------------------------------------------- */
/* METHDOS */

sdk_err_t sdk_ringbuffer_init(sdk_ringbuffer_t* buf, uint8_t* buffer, sdk_size_t buffer_size);

void sdk_ringbuffer_reset(sdk_ringbuffer_t * buf);

C_STATIC_FORCE_INLINE sdk_bool_t sdk_ringbuffer_is_empty(sdk_ringbuffer_t* buf){
    return (buf->write_idx==buf->read_idx)?SDK_TRUE:SDK_FALSE;
}

C_STATIC_FORCE_INLINE sdk_bool_t sdk_ringbuffer_is_full(sdk_ringbuffer_t* buf){
    sdk_size_t next_write_idx = buf->write_idx+1;
    if(next_write_idx==buf->buffer_size){
        next_write_idx = 0;
    }
    return (next_write_idx==buf->read_idx)?SDK_TRUE:SDK_FALSE;
}

C_STATIC_FORCE_INLINE sdk_size_t sdk_ringbuffer_used(sdk_ringbuffer_t* buf){
    sdk_size_t write_idx = buf->write_idx;
    sdk_size_t read_idx = buf->read_idx;
    if(write_idx>=read_idx){
        /* 0 1 2 3 4
             |   |- w
             |-r
        */
        return (write_idx-read_idx);
    }else{
        /* 0 1 2 3 4
             |- w|
                 |-r
         */
        return (buf->buffer_size - read_idx + write_idx);
    }
}

C_STATIC_FORCE_INLINE sdk_size_t sdk_ringbuffer_available(sdk_ringbuffer_t* buf){
    return buf->buffer_size - sdk_ringbuffer_used(buf);
}

sdk_err_t sdk_ringbuffer_put(sdk_ringbuffer_t* buf, uint8_t data);

/* 将读取指针往前移动 idx 个位置，当 idx > used 为检查错误 */
sdk_err_t sdk_ringbuffer_advance(sdk_ringbuffer_t* buf, sdk_size_t idx);

/* 读取一个数据，并将读取指针往前移动一个位置，当buf为空时为检查错误 */
sdk_err_t sdk_ringbuffer_pop(sdk_ringbuffer_t* buf, uint8_t* data);

/* 读取idx位置数据，读取指针不变化，当 idx > used 时为检查错误 */
sdk_err_t sdk_ringbuffer_peek(sdk_ringbuffer_t* buf, sdk_size_t idx, uint8_t* data);

uint8_t sdk_ringbuffer_get(sdk_ringbuffer_t* buf, sdk_size_t idx);

/* 将数据批量写入buffer, 当空间不够时为检查错误 */
sdk_err_t sdk_ringbuffer_write(sdk_ringbuffer_t* buf, uint8_t* data, sdk_size_t size);

unsigned long sdk_ringbuffer_strtoul(sdk_ringbuffer_t* buf, sdk_size_t idx, sdk_size_t * endptr, int base);

int sdk_ringbuffer_find(sdk_ringbuffer_t* buf, sdk_size_t from_idx, const uint8_t* data, sdk_size_t data_size);

int sdk_ringbuffer_find_str(sdk_ringbuffer_t * buf, sdk_size_t from_idx, const char* str);

sdk_err_t sdk_ringbuffer_cut(sdk_ringbuffer_t* buf, sdk_size_t from_idx, const char* prefix, const char* postfix, sdk_ringbuffer_pos_t* pos);

#endif /* INCLUDED_SDK_RINGBUFFER_H */
