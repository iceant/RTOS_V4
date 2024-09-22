#include <os_idle.h>
#include <os_thread.h>
#include <os_macros.h>
/* -------------------------------------------------------------------------------------------------------------- */
/* STATIC */

static os_idle_action_t os_idle__action;
static uint8_t os_idle__stack[OS_THREAD_IDLE_STACK_SIZE];
static os_thread_t os_idle__thread;

static void os_idle__thread_entry(void* p){
    while(1){
        if(os_idle__action){
            os_idle__action();
        }
    }
}
/* -------------------------------------------------------------------------------------------------------------- */
/*  */

void os_idle_startup(void){
    os_idle__action = 0;
    os_thread_init(&os_idle__thread, "idle", os_idle__thread_entry, 0
        , os_idle__stack, OS_THREAD_IDLE_STACK_SIZE
        , OS_THREAD_IDLE_PRIORITY, OS_THREAD_IDLE_TICKS, 0, 0);
    os_thread_startup(&os_idle__thread);
}

void os_idle_set_action(os_idle_action_t action){
    os_idle__action = action;
}

