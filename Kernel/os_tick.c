#include <os_tick.h>

os_tick_t os_tick_from_millisecond(os_uint_t ms)
{
    os_tick_t tick;
    tick = (os_tick_t)((ms * OS_TICK_PER_SECOND)/1000u);
    if(tick==0 && ms!=0){
        tick = 1;
    }
    return tick;
}
