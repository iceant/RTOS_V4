#include <os_interrupt.h>
#include <os_scheduler.h>

/* -------------------------------------------------------------------------------------------------------------- */
/* STATIC */

static os_uint_t os_interrupt__nest=0;

/* -------------------------------------------------------------------------------------------------------------- */
/* METHDOS */

void os_interrupt_enter(void){
    os_interrupt__nest++;
}

void os_interrupt_leave(void){
    os_interrupt__nest--;
    if(os_interrupt__nest==0u){
        if(os_scheduler_is_need_schedule()){
            os_scheduler_set_need_schedule(0);
            os_scheduler_schedule();
        }
    }
}

os_bool_t os_interrupt_is_nest(void){
    return os_interrupt__nest>0u;
}
