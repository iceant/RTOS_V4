#include <os_timewheel.h>
#include <os_types.h>
#include <os_list.h>
#include <os_macros.h>
/* -------------------------------------------------------------------------------------------------------------- */
/*  */
#define TWR_BITS 8
#define TWN_BITS 6
#define TWN_NBR  4

#define TWR_SIZE         (1<<TWR_BITS)  /* 256, 0x100 */
#define TWN_SIZE         (1<<TWR_BITS)  /* 64,  0x40 */

#define TWN_MASK         (TWN_SIZE-1)   /* 0x3F */

#define TWR_MAX         (TWR_SIZE-1)                        /* 0xFF */
#define TWN_MAX(N)      ((1<<(TWR_BITS + (N) * TWN_BITS))-1)

#define TWN_IDX(T, N)      (((T)>>(TWR_BITS + (N)*TWN_BITS)) & TWN_MASK)

/* -------------------------------------------------------------------------------------------------------------- */
/*
31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
|                 |                 |                 |                 |
*/


/* -------------------------------------------------------------------------------------------------------------- */
/* STATIC */
static os_tick_t os_timewheel__tick;
static os_list_t os_timewheel__root_list[TWR_SIZE];
static os_list_t os_timewheel__n_list[TWN_NBR][TWN_SIZE];

C_STATIC_FORCE_INLINE os_list_t* os_timewheel__find_slot(os_tick_t tick){
    if(tick < TWR_SIZE){
        return &os_timewheel__root_list[tick];
    }else if(tick <= TWN_MAX(1)){
        return &os_timewheel__n_list[0][TWN_IDX(tick, 0)];
    }else if(tick <= TWN_MAX(2)){
        return &os_timewheel__n_list[1][TWN_IDX(tick, 1)];
    }else if(tick <= TWN_MAX(3)){
        return &os_timewheel__n_list[2][TWN_IDX(tick, 2)];
    }else if(tick <= 0xFFFFFFFFu){
        return &os_timewheel__n_list[3][TWN_IDX(tick, 3)];
    }
    return 0;
}
/* -------------------------------------------------------------------------------------------------------------- */
/* METHDO */

os_err_t os_timewheel_init(void)
{
    os_size_t i;
    os_size_t j;
    
    os_timewheel__tick = 0;
    
    for(i=0; i< TWR_SIZE; i++){
        OS_LIST_INIT(&os_timewheel__root_list[i]);
    }
    
    for(i=0; i<TWN_NBR; i++){
        for(j=0; j<TWN_SIZE; j++){
            OS_LIST_INIT(&os_timewheel__n_list[i][j]);
        }
    }
    
    return OS_ERR_OK;
}

os_err_t os_timewheel_add_timer(os_timer_t* timer, os_timer_function_t fn, void* userdata, os_tick_t ticks, int flag)
{
    os_tick_t tick_now = os_timewheel__tick;
    
    os_timer_init(timer, fn, userdata, ticks, flag);
    timer->expire_tick = timer->period_tick + tick_now;
    
    os_list_t * slot_list = os_timewheel__find_slot(timer->expire_tick);
    OS_LIST_INSERT_BEFORE(slot_list, &timer->wait_node);
    
    return OS_ERR_OK;
}

os_err_t os_timewheel_tick(void){
    
    os_list_node_t* node_p;
    os_timer_t* timer_p;
    os_tick_t tick_now;
    os_err_t err = OS_ERR_OK;
    
    os_timewheel__tick++;
    
    tick_now = os_timewheel__tick;
    
    os_list_t * slot_list = os_timewheel__find_slot(tick_now);
    
    for(node_p = OS_LIST_NEXT(slot_list); node_p!=slot_list; ){
        timer_p = OS_LIST_CONTAINER(node_p, os_timer_t, wait_node);
        node_p = OS_LIST_NEXT(node_p);
        if(timer_p->expire_tick <= tick_now){
            OS_LIST_REMOVE(&timer_p->wait_node);
            /*timeout*/
            err = OS_TIMEWHEEL_ERR_NEED_SCHEDULE;
            if(timer_p->timer_function){
                timer_p->timer_function(timer_p);
            }
        }
        if(timer_p->flag == OS_TIMER_FLAG_REPEAT){
            timer_p->expire_tick = timer_p->period_tick + tick_now;
            os_list_t * list = os_timewheel__find_slot(timer_p->expire_tick);
            OS_LIST_INSERT_BEFORE(list, &timer_p->wait_node);
        }
    }
    
    return err;
}

os_tick_t os_timewheel_get_tick(void){
    return os_timewheel__tick;
}

