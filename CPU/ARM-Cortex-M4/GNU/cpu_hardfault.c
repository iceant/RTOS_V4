#include <cpu_hardfault.h>

__attribute__((naked)) void HardFault_Handler(void)
{
__asm volatile(
        ".global HardFault_Handler_C\n"
        "PRESERVE8 \n"
        "   CPSID       I \n"
        "   TST LR,     #4 \n"
        "   ITE         EQ \n"
        "   MRSEQ       R0, MSP \n"
        "   MRSNE       R0, PSP \n"
        "   MOV         R1, LR \n"
        "   B           HardFault_Handler_C \n"
        "   .align 4 \n"
        );
}
