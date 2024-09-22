#include <cpu_svc_handler.h>
#include <cpu_types.h>
#include <cpu_svc.h>

cpu_uint_t svc_exc_return;
void SVC_Handler_C(cpu_uint_t* svc_args);

__attribute__((naked)) void SVC_Handler(void){
    __asm__ volatile(
            ".global SVC_Handler_C      \n"
            "TST LR, #4                 \n"
            "ITE EQ                     \n"
            "MRSEQ R0, MSP              \n"
            "MRSNE R0, PSP              \n"
            "LDR R1, =svc_exc_return    \n"
            "STR LR, [R1]               \n"
            "BL SVC_Handler_C           \n"
            "LDR R1, =svc_exc_return    \n"
            "LDR LR, [R1]               \n"
            "BX LR                      \n"
            ".align 4"
    );
}

void SVC_Handler_C(cpu_uint_t* svc_args){
    uint8_t svc_number;
    svc_number = ((char*)svc_args[6])[-2];
    cpu_svc_function_t fn = cpu_svc_get_function(svc_number);
    if(fn){
        fn(svc_args, (void*)&svc_args[0]);
    }
}
