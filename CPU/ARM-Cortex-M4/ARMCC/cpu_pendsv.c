#include <cpu_pendsv.h>
#include <cpu_private.h>

__asm void PendSV_Handler(void){
    
    IMPORT cpu_stack_switch_flag
    IMPORT cpu_stack_switch_from_p
    IMPORT cpu_stack_switch_to_p
    IMPORT cpu_stack_switch_on_success
    
    PRESERVE8

        MRS R1, PRIMASK
        CPSID I
        
        LDR R0, =cpu_stack_switch_flag
        LDR R2, [R0]
        CBZ R2, __PendSV_Exit /* if(cpu_stack_switch_flag==0) goto __PendSV_Exit; */
        
        MOV R2, #0x00
        STR R2, [R0]    /* cpu_stack_switch_flag=0 */
        
        LDR R2, =cpu_stack_switch_from_p
        LDR R0, [R2]
        CBZ R0, __PendSV_SwitchTo /* if(cpu_stack_switch_from_p==0) goto __PendSV_SwitchTo; */
        
        MRS R0, PSP     /* Save Current Stack From PSP */
    #ifdef __FPU_PRESENT
        TST LR, #0x10
        IT EQ
        VSTMDBEQ R0!, {S16-S31}
    #endif
        MOV R2, LR
        MRS R3, CONTROL
        STMDB R0!, {R2-R11}

        LDR R2, =cpu_stack_switch_from_p
        LDR R3, [R2]
        STR R0, [R3] /* cpu_stack_switch_from_p->sp = PSP */

__PendSV_SwitchTo
        LDR R0, =cpu_stack_switch_to_p
        LDR R0, [R0]
        LDR R0, [R0]

        LDMIA R0!, {R2-R11}
        MOV LR, R2
        MSR CONTROL, R3
        
#ifdef __FPU_PRESENT
        TST LR, #0x10
        IT EQ
        VLDMIAEQ R0!, {S16-S31}
#endif
        
        PUSH {R0, R1, LR};
        BL cpu_stack_switch_on_success
        POP {R0, R1, LR};
        
        MSR PSP, R0

        
__PendSV_Exit
        MSR PRIMASK, R1
        DMB
        ISB
        BX LR

        ALIGN 4

}

