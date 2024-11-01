#include <sdk_ringbuffer.h>
#include <sdk_memory.h>
#include <ctype.h>

/* -------------------------------------------------------------------------------------------------------------- */
/* CONSTANTS */

#ifndef ULONG_MAX
#define	ULONG_MAX	((unsigned long)(~0L))		/* 0xFFFFFFFF */
#endif

/* -------------------------------------------------------------------------------------------------------------- */
/* METHODS */

sdk_err_t sdk_ringbuffer_init(sdk_ringbuffer_t* buf, uint8_t* buffer, sdk_size_t buffer_size)
{
    buf->buffer = buffer;
    buf->buffer_size = buffer_size;
    buf->write_idx = 0;
    buf->read_idx = 0;
    return SDK_ERR_OK;
}

void sdk_ringbuffer_reset(sdk_ringbuffer_t * buf){
    buf->write_idx = 0;
    buf->read_idx = 0;
}

sdk_err_t sdk_ringbuffer_put(sdk_ringbuffer_t* buf, uint8_t data){
    if(sdk_ringbuffer_is_full(buf)){
        return SDK_ERR_FULL;
    }
    sdk_size_t write_idx = buf->write_idx;
    buf->buffer[write_idx] = data;
    write_idx+=1;
    if(write_idx>=buf->buffer_size){
        write_idx = 0;
    }
    buf->write_idx = write_idx;
    return SDK_ERR_OK;
}

sdk_err_t sdk_ringbuffer_write(sdk_ringbuffer_t* buf, uint8_t* data, sdk_size_t size){
    sdk_size_t space = sdk_ringbuffer_available(buf);
    if(space < size){
        return SDK_ERR_NOMEM;
    }
    sdk_err_t err;
    for(sdk_size_t i=0; i<size; i++){
        err = sdk_ringbuffer_put(buf, *data++);
        if(err!=SDK_ERR_OK){
            return err;
        }
    }
    return SDK_ERR_OK;
}

sdk_err_t sdk_ringbuffer_peek(sdk_ringbuffer_t* buf, sdk_size_t idx, uint8_t* data){
    if(sdk_ringbuffer_is_empty(buf)){
        return SDK_ERR_EMPTY;
    }
    if(idx>= sdk_ringbuffer_used(buf)){
        return SDK_ERR_PARAM;
    }
    
    if(data){
        *data = buf->buffer[idx];
    }
    return SDK_ERR_OK;
}

sdk_err_t sdk_ringbuffer_pop(sdk_ringbuffer_t* buf, uint8_t* data){
    if(sdk_ringbuffer_is_empty(buf)){
        return SDK_ERR_EMPTY;
    }
    sdk_size_t read_idx = buf->read_idx;
    if(data){
        *data = buf->buffer[read_idx];
    }
    read_idx+=1;
    if(read_idx==buf->buffer_size){
        read_idx = 0;
    }
    buf->read_idx = read_idx;
    return SDK_ERR_OK;
}

/* 0 1 2 3 4 5
 *     |-w |
 *         |-r
 * */
sdk_err_t sdk_ringbuffer_advance(sdk_ringbuffer_t* buf, sdk_size_t idx){
    sdk_size_t used = sdk_ringbuffer_used(buf);
    if(idx > used){
        return SDK_ERR_PARAM;
    }
    
    /*
     * read_idx = 4, idx=3, buf_size = 6
     * read_idx = (read_idx+idx) - buf_size = 1
     */
    
    sdk_size_t read_idx = buf->read_idx;
    read_idx += idx;
    if(read_idx>=buf->buffer_size){
        read_idx -= buf->buffer_size;
    }

    
//    sdk_size_t read_idx = buf->read_idx;
//    for(sdk_size_t i=0; i<idx; i++){
//        read_idx+=1;
//        if(read_idx>=buf->buffer_size){
//            read_idx = 0;
//        }
//    }
    return SDK_ERR_OK;
}

uint8_t sdk_ringbuffer_get(sdk_ringbuffer_t* buf, sdk_size_t idx){
    if(sdk_ringbuffer_is_empty(buf)){
        return -1;
    }
    if(idx> sdk_ringbuffer_used(buf)){
        return -1;
    }
    return buf->buffer[idx];
}

sdk_bool_t sdk_ringbuffer_is(sdk_ringbuffer_t * buf, sdk_size_t idx, uint8_t data){
    return (sdk_ringbuffer_get(buf, idx)==data)?SDK_TRUE:SDK_FALSE;
}

/* 从 idx (idx < used) 位置开始将数据转换为 unsigned long, 结束位置存入 endptr 中*/
unsigned long sdk_ringbuffer_strtoul(sdk_ringbuffer_t* buf, sdk_size_t idx, sdk_size_t * endptr, int base)
{
    register sdk_size_t d_idx = idx;
    register unsigned long acc;
    register unsigned long cutoff;
    register int neg = 0, any, cutlim;
    uint8_t c;
    
    if(idx > sdk_ringbuffer_used(buf)){
        return SDK_ERR_PARAM;
    }
    
    /*
     * See strtol for comments as to the logic used.
     */
    do {
//        c = *s++;
        c = sdk_ringbuffer_get(buf, d_idx++);
    } while (isspace(c));
    if (c == '-') {
        neg = 1;
//        c = *s++;
        c = sdk_ringbuffer_get(buf, d_idx++);
    } else if (c == '+'){
        c = sdk_ringbuffer_get(buf, d_idx++);
//        c = *s++;
    }
//    if ((base == 0 || base == 16) &&
//        c == '0' && (*s == 'x' || *s == 'X')) {
//        c = s[1];
//        s += 2;
//        base = 16;
//    }
    if ((base == 0 || base == 16) &&
        c == '0' && (sdk_ringbuffer_get(buf, d_idx) == 'x' || sdk_ringbuffer_get(buf, d_idx) == 'X')) {
//        c = s[1];
//        s += 2;
        c = sdk_ringbuffer_get(buf, d_idx+1);
        d_idx+=2;
        base = 16;
    }
    if (base == 0)
        base = c == '0' ? 8 : 10;
    cutoff = (unsigned long)ULONG_MAX / (unsigned long)base;
    cutlim = (unsigned long)ULONG_MAX % (unsigned long)base;
//    for (acc = 0, any = 0;; c = *s++)
    for (acc = 0, any = 0;; c = sdk_ringbuffer_get(buf, d_idx++))
    {
        if (isdigit(c))
            c -= '0';
        else if (isalpha(c))
            c -= isupper(c) ? 'A' - 10 : 'a' - 10;
        else
            break;
        if (c >= base)
            break;
        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
            any = -1;
        else {
            any = 1;
            acc *= base;
            acc += c;
        }
    }
    if (any < 0) {
        acc = ULONG_MAX;
    } else if (neg)
        acc = -acc;
    if (endptr != 0)
        *endptr = (any ? d_idx - 1 : idx);
    return (acc);
}

int sdk_ringbuffer_find(sdk_ringbuffer_t* buf, sdk_size_t from_idx, const uint8_t* data, sdk_size_t data_size){
    sdk_size_t used = sdk_ringbuffer_used(buf);
    if(from_idx> used){
        return SDK_ERR_PARAM;
    }
    
    if(data_size > (used - from_idx)){
        return SDK_ERR_PARAM;
    }
    
    sdk_size_t i;
    sdk_size_t j;
    for(i=from_idx; i<used; ){
        for(j=0; j<data_size; j++){
            if(sdk_ringbuffer_get(buf, i+j)!=data[j]){
                i++;
                break;
            }
        }
        if(j==data_size){
            return (int)i;
        }
    }
    
    return SDK_ERR_ERROR;
}

int sdk_ringbuffer_find_str(sdk_ringbuffer_t * buf, sdk_size_t from_idx, const char* str){
    return sdk_ringbuffer_find(buf, from_idx, (const uint8_t*)str, strlen(str));
}

sdk_err_t sdk_ringbuffer_cut(sdk_ringbuffer_t* buf, sdk_size_t from_idx
                             , const char* prefix, const char* postfix, sdk_ringbuffer_pos_t* pos){
    int find_start = sdk_ringbuffer_find_str(buf, from_idx, prefix);
    if(find_start<0) return find_start;
    
    sdk_size_t prefix_size = strlen(prefix);
    
    int find_end = sdk_ringbuffer_find_str(buf, find_start + prefix_size, postfix);
    if(find_end<0){
        return find_end;
    }
    
    if(pos){
        pos->start = find_start + prefix_size;
        pos->end = find_end;
    }
    
    return SDK_ERR_OK;
}

void sdk_ringbuffer_dump(sdk_ringbuffer_t * buf, const char* name, void (*put)(char*, ...)){
    char ascii[17];
    size_t i, j;
    size_t size = sdk_ringbuffer_used(buf);
    ascii[16] = '\0';
    uint8_t ch;

    if(name){
        put("-- DUMP: %s(%u) --\n", name, size);
    }


    for (i = 0; i < size; ++i) {
        sdk_ringbuffer_peek(buf, i, &ch);
        put("%02X ", ch);
        if (ch >= ' ' && ch <= '~') {
            ascii[i % 16] = ch;
        } else {
            ascii[i % 16] = '.';
        }
        if ((i+1) % 8 == 0 || i+1 == size) {
            put(" ");
            if ((i+1) % 16 == 0) {
                put("|  %s \n", ascii);
            } else if (i+1 == size) {
                ascii[(i+1) % 16] = '\0';
                if ((i+1) % 16 <= 8) {
                    put(" ");
                }
                for (j = (i+1) % 16; j < 16; ++j) {
                    put("   ");
                }
                put("|  %s \n", ascii);
            }
        }
    }
}