#include <os_priority.h>

#define OS_PRIORITY_TABLE_SIZE (((OS_PRIORITY_MAX-1u)/OS_INT_CPU_BITS) + 1u)

/* -------------------------------------------------------------------------------------------------------------- */
/* STATIC */

/*
 * 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
 *  | |  |  |- Priority 3 ...
 *  | |  |- Priority 2
 *  | |- Priority 1
 *  |- Priority 0
 */

static os_priority_t os_priority__table[OS_PRIORITY_TABLE_SIZE];

/* -------------------------------------------------------------------------------------------------------------- */
/* METHODS */
os_err_t os_priority_init(void)
{
    os_size_t i;
    for(i=0; i<OS_PRIORITY_TABLE_SIZE; i++){
        os_priority__table[i] = 0;
    }
    return 0;
}

os_priority_t os_priority_highest(void){
    os_priority_t* table_p;
    os_priority_t  priority;
    priority = 0;
    table_p = &os_priority__table[0];
    while(*table_p == 0){
        priority+=OS_INT_CPU_BITS;
        table_p++;
    }
    priority+=(os_priority_t)cpu_clz(*table_p);
    return priority;
}

void os_priority_mark(os_priority_t priority)
{
    os_size_t bit;
    os_size_t bit_nbr;
    os_priority_t idx;
    
    idx = priority / OS_INT_CPU_BITS;
    bit_nbr = priority & (OS_INT_CPU_BITS - 1u);
    bit = 1u;
    bit <<= (OS_INT_CPU_BITS-1u)-bit_nbr;
    os_priority__table[idx]|=bit;
}

void os_priority_unmark(os_priority_t priority)
{
    os_size_t bit;
    os_size_t bit_nbr;
    os_priority_t idx;
    
    idx = priority / OS_INT_CPU_BITS;
    bit_nbr = priority & (OS_INT_CPU_BITS - 1u);
    bit = 1u;
    bit <<= (OS_INT_CPU_BITS-1u)-bit_nbr;
    os_priority__table[idx]&=~bit;
}


