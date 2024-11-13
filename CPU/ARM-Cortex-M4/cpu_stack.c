#include <cpu_stack.h>
#include <cpu_types.h>

/* -------------------------------------------------------------------------------------------------------------- */
/* MACROS */

#define NVIC_INT_CTRL           (*((volatile cpu_uint_t*)0xE000ED04))
#define NVIC_PENDSVSET          0x10000000

#if defined(__FPU_ENABLE)
    #define CPU_STACK_MINIMAL_SIZE ((18+16)*4)
#else
    #define CPU_STACK_MINIMAL_SIZE (18*4)
#endif



/* -------------------------------------------------------------------------------------------------------------- */
/* STATIC */

cpu_stack_switch_callback_t cpu_stack_switch_on_success_callback;

int             cpu_stack_switch_flag;
volatile void** cpu_stack_switch_from_p;
volatile void** cpu_stack_switch_to_p;

void cpu_stack_switch_on_success(void){
    if(cpu_stack_switch_on_success_callback){
        cpu_stack_switch_on_success_callback((void**)cpu_stack_switch_from_p, (void**)cpu_stack_switch_to_p);
    }
}

/* -------------------------------------------------------------------------------------------------------------- */
/* METHODS */
cpu_int_t cpu_stack_init(void* program_entry_p
        , void* program_parameter
        , uint8_t* stack_address
        , cpu_int_t stack_size
        , void* program_exit_function_p
        , void** return_sp
)
{
    cpu_uint_t * p_stack;
    cpu_uint_t * p_stack_limit;
    
    if(stack_size < CPU_STACK_MINIMAL_SIZE){
        return CPU_STACK_ESIZE;
    }
    
    p_stack = (cpu_uint_t*)(stack_address+stack_size);
    p_stack_limit = (cpu_uint_t*)(stack_address + stack_size - CPU_STACK_MINIMAL_SIZE);
    
    *--p_stack = (cpu_uint_t)0x01000000u;               /* xPSR */
    *--p_stack = (cpu_uint_t)program_entry_p;           /* PC */
    *--p_stack = (cpu_uint_t)program_exit_function_p;   /* R14/LR - Return */
    *--p_stack = (cpu_uint_t)0x12121212u;               /* R12 */
    *--p_stack = (cpu_uint_t)0x03030303u;               /* R3 */
    *--p_stack = (cpu_uint_t)0x02020202u;               /* R2 */
    *--p_stack = (cpu_uint_t)p_stack_limit;             /* R1 */
    *--p_stack = (cpu_uint_t)program_parameter;         /* R0 */
    
    *--p_stack = (cpu_uint_t)0x11111111u;               /* R11 */
    *--p_stack = (cpu_uint_t)0x10101010u;               /* R10 */
    *--p_stack = (cpu_uint_t)0x09090909u;               /* R9 */
    *--p_stack = (cpu_uint_t)0x08080808u;               /* R8 */
    *--p_stack = (cpu_uint_t)0x07070707u;               /* R7 */
    *--p_stack = (cpu_uint_t)0x06060606u;               /* R6 */
    *--p_stack = (cpu_uint_t)0x05050505u;               /* R5 */
    *--p_stack = (cpu_uint_t)0x04040404u;               /* R4 */
    *--p_stack = (cpu_uint_t)0x03u;                     /* R3 - CONTROL = Thread/UnPrivilege */
    *--p_stack = (cpu_uint_t)0xFFFFFFFDu;               /* R2 - LR*/
    
    if(return_sp){
        *return_sp = p_stack;
    }
    
    return CPU_STACK_OK;
}

cpu_int_t cpu_stack_switch(void** from_stack_p, void** to_stack_p, cpu_stack_switch_callback_t on_success)
{
    if(cpu_stack_switch_flag==1){
        /* switch work in progress */
        return CPU_STACK_WIP;
    }
    cpu_stack_switch_flag = 1;
    cpu_stack_switch_from_p = (volatile void**)from_stack_p;
    cpu_stack_switch_to_p = (volatile void**)to_stack_p;
    cpu_stack_switch_on_success_callback = on_success;
    
    /* set pendsv set flag */
    NVIC_INT_CTRL = NVIC_PENDSVSET;
    
    return CPU_STACK_OK;
}

cpu_int_t cpu_stack_check(void* stack_addr, cpu_uint_t stack_size_nBytes, void* sp){
    cpu_uintptr_t stack_bottom = ((cpu_uintptr_t)stack_addr) + stack_size_nBytes;
    cpu_uintptr_t uint_sp = (cpu_uintptr_t)sp;
    cpu_uintptr_t stack_limit = ((cpu_uintptr_t)stack_addr) + CPU_STACK_MINIMAL_SIZE;
    
    if(uint_sp>=stack_limit && uint_sp <=stack_bottom){
        return CPU_STACK_OK;
    }
    
    return CPU_STACK_OVERFLOW;
}

cpu_uint_t cpu_stack_remain(void* stack_addr, cpu_uint_t stack_size_nBytes, void* sp){
    cpu_uintptr_t stack_bottom = (cpu_uintptr_t)stack_addr;
    cpu_uintptr_t uint_sp = (cpu_uintptr_t)sp;
    return (uint_sp - stack_bottom);
}
