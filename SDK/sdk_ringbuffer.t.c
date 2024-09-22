#include <sdk_ringbuffer.h>
#include <stdio.h>
#include <stdlib.h>
#include <sdk_hex.h>

#define BLOCK_SIZE 257
static uint8_t block[BLOCK_SIZE];
static sdk_ringbuffer_t buffer;

int main(int argc, char** argv){
    sdk_ringbuffer_init(&buffer, block, BLOCK_SIZE);
    for(int i=0; i<=0xFF; i++){
        sdk_ringbuffer_put(&buffer, i);
    }
    
    SDK_HEX_DUMP("Buffer", buffer.buffer, sdk_ringbuffer_used(&buffer));
    sdk_size_t end_idx = 0;
    unsigned long ulValue = sdk_ringbuffer_strtoul(&buffer, '0', &end_idx, 10);
    printf("ulValue:%lu, end_idx:%d\n", ulValue, end_idx);
    
    int find = sdk_ringbuffer_find_str(&buffer, 42, "789");
    printf("find: %d\n", find);
    sdk_ringbuffer_pos_t pos;
    int cut = sdk_ringbuffer_cut(&buffer, 'A', "DEF", "XYZ", &pos);
    printf("cut[%d, %d]:", pos.start, pos.end);
    for(sdk_size_t i=pos.start; i<pos.end; i++){
        printf("%c", sdk_ringbuffer_get(&buffer, i));
    }
    printf("\n");
    
    return 0;
}