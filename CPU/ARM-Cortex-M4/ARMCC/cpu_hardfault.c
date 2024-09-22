#include <cpu_hardfault.h>

__asm void HardFault_Handler(void)
{

    IMPORT HardFault_Handler_C
    PRESERVE8
    
        CPSID       I
        TST LR,     #4
        ITE         EQ
        MRSEQ       R0, MSP
        MRSNE       R0, PSP
        MOV         R1, LR
        B           HardFault_Handler_C         
    
    ALIGN 4
}



