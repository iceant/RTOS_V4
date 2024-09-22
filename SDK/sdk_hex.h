#ifndef INCLUDED_SDK_HEX_H
#define INCLUDED_SDK_HEX_H

#ifndef INCLUDED_SDK_TYPES_H
#include <sdk_types.h>
#endif /*INCLUDED_SDK_TYPES_H*/

#ifndef INCLUDED_STDIO_H
#define INCLUDED_STDIO_H
#include <stdio.h>
#endif /*INCLUDED_STDIO_H*/




////////////////////////////////////////////////////////////////////////////////
////

typedef enum sdk_byteorder_e{
    kSDK_ByteOrder_LittleEndian=0,
    kSDK_ByteOrder_BigEndian=1,
}sdk_byteorder_t;

typedef void (*sdk_hex_printf)(const char* fmt, ...);

void sdk_hex_dump(const char* name, const void* data, int size, sdk_hex_printf put);

////////////////////////////////////////////////////////////////////////////////
////
size_t sdk_hex_encode(char* buffer, uint32_t offset, size_t buffer_size, const uint8_t *data
                        , size_t data_offset, size_t data_size, bool isUpperCase, sdk_byteorder_t byteOrder);

size_t sdk_hex_decode(uint8_t *buffer, size_t buffer_offset, size_t buffer_size
                        , const char* hex, size_t hex_offset, size_t hex_size);

/* -------------------------------------------------------------------------------------------------------------- */
/* UTILS */

#define SDK_HEX_DUMP(Name, Data, Size) sdk_hex_dump((Name), (Data), (Size), (sdk_hex_printf)printf)

#define SDK_HEX_ENCODE_BE(result, result_size, data, data_size) sdk_hex_encode((result), 0, (result_size), (data), 0, (data_size), true, kSDK_ByteOrder_BigEndian)
#define SDK_HEX_ENCODE_LE(result, result_size, data, data_size) sdk_hex_encode((result), 0, (result_size), (data), 0, (data_size), true, kSDK_ByteOrder_LittleEndian)

#define SDK_HEX_DECODE(buffer, buffer_size, hex_string, hex_string_length) sdk_hex_decode((uint8_t*)(buffer), 0, (buffer_size), (const char*)(hex_string), 0, (hex_string_length))

#define SDK_HEX_SET_UINT8(array, idx, u8v) ((array)[(idx)]=(u8v)&0xFF)

#define SDK_HEX_SET_UINT16_BE(array, idx, u16v) \
do{                                            \
    (array)[(idx)] = ((u16v) >> 8) & 0xFF;     \
    (array)[(idx)+1] = ((u16v)) & 0xFF;        \
}while(0)

#define SDK_HEX_SET_UINT16_LE(array, idx, u16v)  \
do{                                             \
    (array)[(idx)] = ((u16v)) & 0xFF;           \
    (array)[(idx)+1] = ((u16v) >> 8) & 0xFF;    \
}while(0)

#define SDK_HEX_SET_UINT24_BE(array, idx, u24v)  \
do{                                             \
    (array)[(idx)] = ((u24v) >> 16) & 0xFF;     \
    (array)[(idx)+1] = ((u24v) >> 8) & 0xFF;    \
    (array)[(idx)+2] = ((u24v)) & 0xFF;         \
}while(0)

#define SDK_HEX_SET_UINT24_LE(array, idx, u24v)  \
do{                                             \
    (array)[(idx)] = ((u24v)) & 0xFF;           \
    (array)[(idx)+1] = ((u24v) >> 8) & 0xFF;    \
    (array)[(idx)+2] = ((u24v) >> 16) & 0xFF;   \
}while(0)

#define SDK_HEX_SET_UINT32_BE(array, idx, u32v) \
do{                                            \
    (array)[(idx)] = ((u32v) >> 24) & 0xFF;    \
    (array)[(idx)+1] = ((u32v) >> 16) & 0xFF;  \
    (array)[(idx)+2] = ((u32v) >> 8) & 0xFF;   \
    (array)[(idx)+3] = ((u32v)) & 0xFF;        \
}while(0)

#define SDK_HEX_SET_UINT32_LE(array, idx, u32v)  \
do{                                             \
    (array)[(idx)] = ((u32v)) & 0xFF;           \
    (array)[(idx)+1] = ((u32v) >> 8) & 0xFF;    \
    (array)[(idx)+2] = ((u32v) >> 16) & 0xFF;   \
    (array)[(idx)+3] = ((u32v) >> 24) & 0xFF;   \
}while(0)



#define SDK_HEX_GET_UINT8(array, idx) (((array)[(idx)])&0xFF)

#define SDK_HEX_GET_UINT16_BE(array, idx) ((((array)[(idx)]&0xFF)<<8) | ((array)[(idx)+1] & 0xFF))
#define SDK_HEX_GET_UINT16_LE(array, idx) (((array)[(idx)]&0xFF) | (((array)[(idx)+1] & 0xFF)<<8) )

#define SDK_HEX_GET_UINT24_BE(array, idx) ( (((array)[(idx)]&0xFF)<<16) | (((array)[(idx)+1]&0xFF)<<8) | ((array)[(idx)+2] & 0xFF) )
#define SDK_HEX_GET_UINT24_LE(array, idx) ( ((array)[(idx)]&0xFF) | (((array)[(idx)+1]&0xFF)<<8) | (((array)[(idx)+2]&0xFF)<<16) )

#define SDK_HEX_GET_UINT32_BE(array, idx) ( (((array)[(idx)]&0xFF)<<24) | (((array)[(idx)+1]&0xFF)<<16) | (((array)[(idx)+2]&0xFF)<<8) | ((array)[(idx)+3] & 0xFF) )
#define SDK_HEX_GET_UINT32_LE(array, idx) ( ((array)[(idx)]&0xFF) | (((array)[(idx)+1]&0xFF)<<8) | (((array)[(idx)+2]&0xFF)<<16) | (((array)[(idx)+3]&0xFF)<<24) )



#endif /*INCLUDED_SDK_HEX_H*/
