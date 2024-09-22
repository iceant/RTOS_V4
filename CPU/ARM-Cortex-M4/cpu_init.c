#include <cpu_init.h>
#include <cpu_exception.h>
#include <cpu_private.h>

void cpu_init(void){
    cpu_stack_switch_flag = 0;
    cpu_stack_switch_on_success_callback = 0;
    cpu_svc_register_init();
    cpu_exception_set_handler(0);
}

