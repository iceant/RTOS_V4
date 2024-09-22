#include <cpu_exception.h>
#include <stdio.h>
#include <cpu_macros.h>
#include <cpu_functions.h>
/* -------------------------------------------------------------------------------------------------------------- */
/* CONSTANTS */

#define SCB_ICSR    0xE000ED04
#define SCB_CFSR    0xE000ED28
#define SCB_HFSR    0xE000ED2C
#define SCB_DFSR    0xE000ED30
#define SCB_MMFAR   0xE000ED34
#define SCB_BFAR    0xE000ED38
#define SCB_AFSR    0xE000ED3C


/* -------------------------------------------------------------------------------------------------------------- */
/* TYPE */

typedef struct __attribute__((packed)) ContextStateFrame_s {
  uint32_t r0;
  uint32_t r1;
  uint32_t r2;
  uint32_t r3;
  uint32_t r12;
  uint32_t lr;
  uint32_t return_address;
  uint32_t xpsr;
} ContextStateFrame_t;

/* -------------------------------------------------------------------------------------------------------------- */
/* STATIC */

static cpu_exception_handler_t cpu_exception__handler=0;
/* -------------------------------------------------------------------------------------------------------------- */
/* METHODS */
void cpu_exception_set_handler(cpu_exception_handler_t handler)
{
    cpu_exception__handler = handler;
}

void cpu_exception_handle_exception(void* args){
    if(cpu_exception__handler){
        cpu_exception__handler(args);
    }
    
    /* CPU SPECIFIED EXCEPTION HANDLER */
}

/* -------------------------------------------------------------------------------------------------------------- */
/* METHODS*/

// NOTE: If you are using CMSIS, the registers can also be
// accessed through CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk
#define HALT_IF_DEBUGGING()                              \
  do {                                                   \
    if ((*(volatile uint32_t *)0xE000EDF0) & (1 << 0)) { \
      __asm("bkpt 1");                                   \
    }                                                    \
} while (0)
  


static void Show_CFSR(volatile cpu_uint_t CFSR){       
    uint8_t MFSR = CFSR & 0xFF;
    uint8_t BFSR = (CFSR >> 8) & 0xFF;
    uint16_t UFSR = (CFSR >> 16) & 0xFFFF;
    
    printf("%8s: %02x (", "MFSR", MFSR);
    if(CPU_BIT_GET(CFSR, 7)){
        printf("MMARVALID ");
    }
    if(CPU_BIT_GET(CFSR, 5)){
        printf("MLSPERR ");
    }
    if(CPU_BIT_GET(CFSR, 4)){
        printf("MSTKERR ");
    }
    if(CPU_BIT_GET(CFSR, 3)){
        printf("MUNSTKERR ");
    }
    if(CPU_BIT_GET(CFSR, 1)){
        printf("DACCVIOL ");
    }
    if(CPU_BIT_GET(CFSR, 0)){
        printf("IACCVIOL ");
    }
    printf(")\n");
    
    printf("%8s: %02x (", "BFSR", BFSR);
    if(CPU_BIT_GET(CFSR, 15)){
        printf("BFARVALID ");
    }
    if(CPU_BIT_GET(CFSR, 13)){
        printf("LSPERR ");
    }
    if(CPU_BIT_GET(CFSR, 12)){
        printf("STKERR ");
    }    
    if(CPU_BIT_GET(CFSR, 11)){
        printf("UNSTKERR ");
    }
    if(CPU_BIT_GET(CFSR, 10)){
        printf("IMPRECISERR ");
    }
    if(CPU_BIT_GET(CFSR, 9)){
        printf("PRECISERR ");
    }
    if(CPU_BIT_GET(CFSR, 8)){
        printf("IBUSERR ");
    }
    printf(")\n");
    
    
    
    printf("%8s: %04x (", "UFSR", UFSR);
    if(CPU_BIT_GET(CFSR, 25)){
        printf("DIVBYZERO ");
    }
    if(CPU_BIT_GET(CFSR, 24)){
        printf("UNALIGNED ");
    }
    if(CPU_BIT_GET(CFSR, 19)){
        printf("NOCP ");
    }
    if(CPU_BIT_GET(CFSR, 18)){
        printf("INVPC ");
    }
    if(CPU_BIT_GET(CFSR, 17)){
        printf("INVSTATE ");
    }
    if(CPU_BIT_GET(CFSR, 16)){
        printf("UNDEFINSTR ");
    }
    printf(")\n");
    
}

void Show_HFSR(volatile cpu_uint_t HFSR){
    printf(" (");
    if(CPU_BIT_GET(HFSR, 31)){
        printf("DEBUGEVT ");
    }
    if(CPU_BIT_GET(HFSR, 30)){
        printf("FORCED ");
    }    
    if(CPU_BIT_GET(HFSR, 1)){
        printf("VECTBL ");
    }
    printf(")\n");
}

void Show_DFSR(volatile cpu_uint_t DFSR){
    printf(" (");
    if(CPU_BIT_GET(DFSR, 4)){
        printf("EXTERNAL ");
    }
    if(CPU_BIT_GET(DFSR, 3)){
        printf("VCATCH ");
    }
    if(CPU_BIT_GET(DFSR, 2)){
        printf("DWTTRAP ");
    }
    if(CPU_BIT_GET(DFSR, 1)){
        printf("BKPT ");
    }
    if(CPU_BIT_GET(DFSR, 0)){
        printf("HALTED ");
    }
    printf(")\n");
}


static void Show_xPSR(volatile cpu_uint_t xPSR){
    printf(" (");
    uint8_t IRQn = (xPSR & 0xFF);
    if( IRQn != 0){
        printf("IRQn: %d(%x) ", IRQn, IRQn);
    }
    if(CPU_BIT_GET(xPSR, 31)){
        printf("N ");
    }
    if(CPU_BIT_GET(xPSR, 30)){
        printf("Z ");
    }
    if(CPU_BIT_GET(xPSR, 29)){
        printf("C ");
    }
    if(CPU_BIT_GET(xPSR, 28)){
        printf("V ");
    }
    if(CPU_BIT_GET(xPSR, 27)){
        printf("Q ");
    }
    if(((xPSR>>24) & 0x3)!=0){
        printf("ICI/IT[25:26]: %d", (xPSR>>24) & 0x3);
    }
    if(CPU_BIT_GET(xPSR, 24)){
        printf("T ");
    }
    if(((xPSR>>15) & 0xF)!=0){
        printf("GE: %d\n", (xPSR>>15) & 0xF);
    }
    if(((xPSR>>9) & 0x3F)!=0){
        printf("ICI/IT[15:10]: %d", (xPSR>>9) & 0x3F);
    }
    printf(")\n");
}

#define CPU_EXCEPTION_RESET_ENABLE

__attribute__((weak)) void recover_from_task_fault(void){
    while(1){
        //vTaskDelay(1);
    }
}

static void Show_LR(volatile cpu_uint_t lr_value){
    if(lr_value==0xFFFFFFE1){
        printf("ISR/MSP/FPCA=1");
    }else if(lr_value==0xFFFFFFF1){
        printf("ISR/MSP/FPCA=0");
    }else if(lr_value==0xFFFFFFE9){
        printf("THD/MSP/FPCA=1");
    }else if(lr_value==0xFFFFFFF9){
        printf("THD/MSP/FPCA=0");
    }else if(lr_value==0xFFFFFFED){
        printf("ISR/PSP/FPCA=1");
    }else if(lr_value==0xFFFFFFFD){
        printf("ISR/PSP/FPCA=0");
    }
}

void HardFault_Handler_C(ContextStateFrame_t* frame, cpu_uint_t lr_value)
{
    volatile cpu_uint_t R0;
    volatile cpu_uint_t R1;
    volatile cpu_uint_t R2;
    volatile cpu_uint_t R3;
    volatile cpu_uint_t R12;
    volatile cpu_uint_t LR;
    volatile cpu_uint_t PC;
    volatile cpu_uint_t xPSR;
    volatile cpu_uint_t CFSR;
    volatile cpu_uint_t HFSR;
    volatile cpu_uint_t DFSR;
    volatile cpu_uint_t AFSR;
    volatile cpu_uint_t BFAR;
    volatile cpu_uint_t MMFAR;
    
    cpu_disable_irq();
    
    BFAR = CPU_REG(SCB_BFAR);
    MMFAR = CPU_REG(SCB_MMFAR);
    CFSR = CPU_REG(SCB_CFSR);
    HFSR = CPU_REG(SCB_HFSR);
    DFSR = CPU_REG(SCB_DFSR);
    AFSR = CPU_REG(SCB_AFSR);

    #if 0
    R0 = ((cpu_uint_t)hardfault_args[0]);
    R1 = ((cpu_uint_t)hardfault_args[1]);
    R2 = ((cpu_uint_t)hardfault_args[2]);
    R3 = ((cpu_uint_t)hardfault_args[3]);
    R12 = ((cpu_uint_t)hardfault_args[4]);
    LR = ((cpu_uint_t)hardfault_args[5]);
    PC = ((cpu_uint_t)hardfault_args[6]);
    xPSR = ((cpu_uint_t)hardfault_args[7]);
   #endif
   
    R0 = ((cpu_uint_t)frame->r0);
    R1 = ((cpu_uint_t)frame->r1);
    R2 = ((cpu_uint_t)frame->r2);
    R3 = ((cpu_uint_t)frame->r3);
    R12 = ((cpu_uint_t)frame->r12);
    LR = ((cpu_uint_t)frame->lr);
    PC = ((cpu_uint_t)frame->return_address);
    xPSR = ((cpu_uint_t)frame->xpsr);
   
    printf("[HardFault]\n");
    printf(" - Stack Frame -:\n");
    printf("%5s = 0x%08x\n", "R0", R0);
    printf("%5s = 0x%08x\n", "R1", R1);
    printf("%5s = 0x%08x\n", "R2", R2);
    printf("%5s = 0x%08x\n", "R3", R3);
    printf("%5s = 0x%08x\n", "R12", R12);
    printf("%5s = 0x%08x\n", "LR", LR);
    printf("%5s = 0x%08x\n", "PC", PC);
    printf("%5s = 0x%08x ", "xPSR", xPSR); Show_xPSR(xPSR);
    
    printf(" - FSR/FAR -:\n");
    printf("%5s = 0x%08x\n", "CFSR", CFSR); Show_CFSR(CFSR);   
    printf("%5s = 0x%08x ", "HFSR", HFSR); Show_HFSR(HFSR);
    printf("%5s = 0x%08x ", "DFSR", DFSR); Show_DFSR(DFSR);
    printf("%5s = 0x%08x\n", "AFSR", AFSR);
    if(CFSR & 0x0080){
        printf("%5s = 0x%08x\n", "MMFAR", MMFAR);
    }
    if(CFSR & 0x8000){
        printf("%5s = 0x%08x\n", "BFAR", BFAR);
    }
    printf(" - MISC -:\n");
    printf("LR/EXC_RETURN = 0x%08x ", lr_value);
    Show_LR(lr_value);
    printf("\n\n\n\n");
        
    // If and only if a debugger is attached, execute a breakpoint
    // instruction so we can take a look at what triggered the fault
  
    HALT_IF_DEBUGGING();
    
    
    // Logic for dealing with the exception. Typically:
    //  - log the fault which occurred for postmortem analysis
    //  - If the fault is recoverable,
    //    - clear errors and return back to Thread Mode
    //  - else
    //    - reboot system
    
    #if defined(CPU_EXCEPTION_RESET_ENABLE)
    
    /* Recovery From Fault, Try to reboot */
    const int non_usage_fault_occurred = (((CFSR >> 16) & 0xFFFF) != 0)?1:0;
    // the bottom 8 bits of the xpsr hold the exception number of the
    // executing exception or 0 if the processor is in Thread mode
    const int faulted_from_exception = ((xPSR & 0xFF) != 0)?1:0;
    
    if (faulted_from_exception || non_usage_fault_occurred) {
    
        // For any fault within an ISR or non-usage faults
        // let's reboot the system
        volatile cpu_uint_t *aircr = (volatile cpu_uint_t*)0xE000ED0C;
        *aircr = (0x05FA << 16) | 0x1 << 2;
        while (1) { } // should be unreachable
    }else{        
        // Clear any logged faults from the CFSR
        CPU_REG(SCB_CFSR) |= CPU_REG(SCB_CFSR);
        // the instruction we will return to when we exit from the exception
        frame->return_address = (uint32_t)recover_from_task_fault;
        // the function we are returning to should never branch
        // so set lr to a pattern that would fault if it did
        frame->lr = 0xdeadbeef;
        // reset the psr state and only leave the
        // "thumb instruction interworking" bit set
        frame->xpsr = (1 << 24);
        
        printf("call recover_from_task_fault()\r\n\r\n");
        
        cpu_enable_irq();
    }


    
    #endif 

    
}
