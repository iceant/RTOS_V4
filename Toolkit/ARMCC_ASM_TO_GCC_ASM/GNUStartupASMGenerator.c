#include <GNUStartupASMGenerator.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

/* -------------------------------------------------------------------------------------------------------------- */
/*  */
#define MIN(a, b) ((a)>(b)?(b):(a))
#define ARRAY_SIZE(A) (sizeof(A)/sizeof(A[0]))



int NVIC_Vector_AddItem(NVIC_VectorItem_T* table, const char* IRQHandler, const char* Comment){
    assert(table);
    assert(IRQHandler);
    assert(Comment);
    
    NVIC_VectorItem_T * p = malloc(sizeof(*p));
    if(!p){
        return -1;
    }
    p->prev = p->next = p;
    
    size_t size = strlen(IRQHandler);
    size = MIN(size, ARRAY_SIZE(table->IRQHandler));
    strncpy(p->IRQHandler, IRQHandler, size);
    p->IRQHandler[size]='\0';
    size = strlen(Comment);
    size = MIN(size, ARRAY_SIZE(table->Comment));
    strncpy(p->Comment, Comment, size);
    p->Comment[size]='\0';
    
    INSERT_BEFORE(table, p);
    
    return 0;
}

void NVIC_Vector_Release(NVIC_VectorItem_T* table)
{
    NVIC_VectorItem_T * p;
    for(p= table->next; p!=table; ){
        NVIC_VectorItem_T * node = p;
        p = p->next;
        free(node);
    }
}

int GNUStartupASMGenerator_Generate(NVIC_VectorItem_T* vectors
                                    , const char* cpu_type, const char* fpu, const char* file){
    FILE * fp = fopen(file, "w+");
    if(!fp) return -1;
    if(cpu_type && fpu){
        fprintf(fp, "\n"
                    "  .syntax unified\n"
                    "  .cpu %s\n"
                    "  .fpu %s\n"
                    "  .thumb\n"
                    "\n"
                    ".global  g_pfnVectors\n"
                    ".global  Default_Handler\n"
                    "\n"
                    "/* start address for the initialization values of the .data section.\n"
                    "defined in linker script */\n"
                    ".word  _sidata\n"
                    "/* start address for the .data section. defined in linker script */\n"
                    ".word  _sdata\n"
                    "/* end address for the .data section. defined in linker script */\n"
                    ".word  _edata\n"
                    "/* start address for the .bss section. defined in linker script */\n"
                    ".word  _sbss\n"
                    "/* end address for the .bss section. defined in linker script */\n"
                    ".word  _ebss\n"
                    "/* stack used for SystemInit_ExtMemCtl; always internal RAM used */\n"
                    "\n"
                    "/**\n"
                    " * @brief  This is the code that gets called when the processor first\n"
                    " *          starts execution following a reset event. Only the absolutely\n"
                    " *          necessary set is performed, after which the application\n"
                    " *          supplied main() routine is called.\n"
                    " * @param  None\n"
                    " * @retval : None\n"
                    "*/\n"
                    "\n"
                    "    .section  .text.Reset_Handler\n"
                    "  .weak  Reset_Handler\n"
                    "  .type  Reset_Handler, %%function\n"
                    "Reset_Handler:\n"
                    "  ldr   sp, =_estack      /* set stack pointer */\n"
                    "\n"
                    "/* Call the clock system initialization function.*/\n"
                    "  bl  SystemInit\n"
                    "\n"
                    "/* Copy the data segment initializers from flash to SRAM */\n"
                    "  ldr r0, =_sdata\n"
                    "  ldr r1, =_edata\n"
                    "  ldr r2, =_sidata\n"
                    "  movs r3, #0\n"
                    "  b LoopCopyDataInit\n"
                    "\n"
                    "CopyDataInit:\n"
                    "  ldr r4, [r2, r3]\n"
                    "  str r4, [r0, r3]\n"
                    "  adds r3, r3, #4\n"
                    "\n"
                    "LoopCopyDataInit:\n"
                    "  adds r4, r0, r3\n"
                    "  cmp r4, r1\n"
                    "  bcc CopyDataInit\n"
                    "/* Zero fill the bss segment. */\n"
                    "  ldr r2, =_sbss\n"
                    "  ldr r4, =_ebss\n"
                    "  movs r3, #0\n"
                    "  b LoopFillZerobss\n"
                    "\n"
                    "FillZerobss:\n"
                    "  str  r3, [r2]\n"
                    "  adds r2, r2, #4\n"
                    "\n"
                    "LoopFillZerobss:\n"
                    "  cmp r2, r4\n"
                    "  bcc FillZerobss\n"
                    "\n"
                    "/* Call static constructors */\n"
                    "    bl __libc_init_array\n"
                    "/* Call the application's entry point.*/\n"
                    "  bl  main\n"
                    "  bx  lr\n"
                    ".size  Reset_Handler, .-Reset_Handler\n"
                    "\n"
                    "/**\n"
                    " * @brief  This is the code that gets called when the processor receives an\n"
                    " *         unexpected interrupt.  This simply enters an infinite loop, preserving\n"
                    " *         the system state for examination by a debugger.\n"
                    " * @param  None\n"
                    " * @retval None\n"
                    "*/\n"
                    "    .section  .text.Default_Handler,\"ax\",%%progbits\n"
                    "Default_Handler:\n"
                    "Infinite_Loop:\n"
                    "  b  Infinite_Loop\n"
                    "  .size  Default_Handler, .-Default_Handler\n"
                    "/******************************************************************************\n"
                    "*\n"
                    "* The minimal vector table for a Cortex M. Note that the proper constructs\n"
                    "* must be placed on this to ensure that it ends up at physical address\n"
                    "* 0x0000.0000.\n"
                    "*\n"
                    "*******************************************************************************/\n"
                    "   .section  .isr_vector,\"a\",%%progbits\n"
                    "  .type  g_pfnVectors, %%object\n"
                    "\n"
                    "\n"
                    "g_pfnVectors:\n"
                    "  .word  _estack\n", cpu_type, fpu);
    }else if(cpu_type && !fpu){
        fprintf(fp, "\n"
                    "  .syntax unified\n"
                    "  .cpu %s\n"
                    "  .thumb\n"
                    "\n"
                    ".global  g_pfnVectors\n"
                    ".global  Default_Handler\n"
                    "\n"
                    "/* start address for the initialization values of the .data section.\n"
                    "defined in linker script */\n"
                    ".word  _sidata\n"
                    "/* start address for the .data section. defined in linker script */\n"
                    ".word  _sdata\n"
                    "/* end address for the .data section. defined in linker script */\n"
                    ".word  _edata\n"
                    "/* start address for the .bss section. defined in linker script */\n"
                    ".word  _sbss\n"
                    "/* end address for the .bss section. defined in linker script */\n"
                    ".word  _ebss\n"
                    "/* stack used for SystemInit_ExtMemCtl; always internal RAM used */\n"
                    "\n"
                    "/**\n"
                    " * @brief  This is the code that gets called when the processor first\n"
                    " *          starts execution following a reset event. Only the absolutely\n"
                    " *          necessary set is performed, after which the application\n"
                    " *          supplied main() routine is called.\n"
                    " * @param  None\n"
                    " * @retval : None\n"
                    "*/\n"
                    "\n"
                    "    .section  .text.Reset_Handler\n"
                    "  .weak  Reset_Handler\n"
                    "  .type  Reset_Handler, %%function\n"
                    "Reset_Handler:\n"
                    "  ldr   sp, =_estack      /* set stack pointer */\n"
                    "\n"
                    "/* Call the clock system initialization function.*/\n"
                    "  bl  SystemInit\n"
                    "\n"
                    "/* Copy the data segment initializers from flash to SRAM */\n"
                    "  ldr r0, =_sdata\n"
                    "  ldr r1, =_edata\n"
                    "  ldr r2, =_sidata\n"
                    "  movs r3, #0\n"
                    "  b LoopCopyDataInit\n"
                    "\n"
                    "CopyDataInit:\n"
                    "  ldr r4, [r2, r3]\n"
                    "  str r4, [r0, r3]\n"
                    "  adds r3, r3, #4\n"
                    "\n"
                    "LoopCopyDataInit:\n"
                    "  adds r4, r0, r3\n"
                    "  cmp r4, r1\n"
                    "  bcc CopyDataInit\n"
                    "/* Zero fill the bss segment. */\n"
                    "  ldr r2, =_sbss\n"
                    "  ldr r4, =_ebss\n"
                    "  movs r3, #0\n"
                    "  b LoopFillZerobss\n"
                    "\n"
                    "FillZerobss:\n"
                    "  str  r3, [r2]\n"
                    "  adds r2, r2, #4\n"
                    "\n"
                    "LoopFillZerobss:\n"
                    "  cmp r2, r4\n"
                    "  bcc FillZerobss\n"
                    "\n"
                    "/* Call static constructors */\n"
                    "    bl __libc_init_array\n"
                    "/* Call the application's entry point.*/\n"
                    "  bl  main\n"
                    "  bx  lr\n"
                    ".size  Reset_Handler, .-Reset_Handler\n"
                    "\n"
                    "/**\n"
                    " * @brief  This is the code that gets called when the processor receives an\n"
                    " *         unexpected interrupt.  This simply enters an infinite loop, preserving\n"
                    " *         the system state for examination by a debugger.\n"
                    " * @param  None\n"
                    " * @retval None\n"
                    "*/\n"
                    "    .section  .text.Default_Handler,\"ax\",%%progbits\n"
                    "Default_Handler:\n"
                    "Infinite_Loop:\n"
                    "  b  Infinite_Loop\n"
                    "  .size  Default_Handler, .-Default_Handler\n"
                    "/******************************************************************************\n"
                    "*\n"
                    "* The minimal vector table for a Cortex M. Note that the proper constructs\n"
                    "* must be placed on this to ensure that it ends up at physical address\n"
                    "* 0x0000.0000.\n"
                    "*\n"
                    "*******************************************************************************/\n"
                    "   .section  .isr_vector,\"a\",%%progbits\n"
                    "  .type  g_pfnVectors, %%object\n"
                    "\n"
                    "\n"
                    "g_pfnVectors:\n"
                    "  .word  _estack\n", cpu_type);
    }
    
    
    NVIC_VectorItem_T * p;
    for(p = vectors->next; p!=vectors; p=p->next){
        fprintf(fp, "  .word  %-50s          /* %s */\n", p->IRQHandler, p->Comment);
    }
    
    fprintf(fp, "  .size  g_pfnVectors, .-g_pfnVectors\n");
    fprintf(fp, "/*******************************************************************************\n"
                "*\n"
                "* Provide weak aliases for each Exception handler to the Default_Handler.\n"
                "* As they are weak aliases, any function with the same name will override\n"
                "* this definition.\n"
                "*\n"
                "*******************************************************************************/\n");
    
    for(p = vectors->next->next; p!=vectors; p=p->next){
        if(strcmp(p->IRQHandler, "0")==0){
            continue;
        }
        fprintf(fp, "   .weak      %s\n"
                    "   .thumb_set %s,Default_Handler\n\n", p->IRQHandler, p->IRQHandler);
    }
    
    fflush(fp);
    fclose(fp);
    
    return 0;
}
