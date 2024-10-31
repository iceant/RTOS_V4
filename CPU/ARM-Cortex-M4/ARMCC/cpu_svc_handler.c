#include <cpu_svc_handler.h>
#include <cpu_types.h>
#include <cpu_svc.h>

cpu_uint_t svc_exc_return;
void SVC_Handler_C(cpu_uint_t* svc_args);

__asm void SVC_Handler(void){
    
    IMPORT SVC_Handler_C
    IMPORT svc_exc_return
        
        TST LR, #4
        ITE EQ
        MRSEQ R0, MSP
        MRSNE R0, PSP
        LDR R1, =svc_exc_return
        STR LR, [R1]
        BL SVC_Handler_C
        LDR R1, =svc_exc_return
        LDR LR, [R1]
        BX LR

    ALIGN 4
}

void SVC_Handler_C(cpu_uint_t* svc_args){
    uint8_t svc_number;
    cpu_svc_function_t fn;
    svc_number = ((char*)svc_args[6])[-2];
    fn = cpu_svc_get_function(svc_number);
    if(fn){
        fn(svc_args, (void*)&svc_args[0]);
    }
}
