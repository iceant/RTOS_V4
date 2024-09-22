#include <os_timer.h>

os_err_t os_timer_init(os_timer_t* timer, os_timer_function_t fn, void* userdata, os_tick_t period_ticks, int flag)
{
    timer->timer_function = fn;
    timer->userdata = userdata;
    timer->period_tick = period_ticks;
    timer->expire_tick = 0;
    timer->flag = flag;
    OS_LIST_INIT(&timer->wait_node);
    
    return OS_ERR_OK;
}


