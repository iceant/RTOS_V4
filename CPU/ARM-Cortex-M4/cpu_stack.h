#ifndef INCLUDED_CPU_STACK_H
#define INCLUDED_CPU_STACK_H

#ifndef INCLUDED_CPU_TYPES_H
#include <cpu_types.h>
#endif /*INCLUDED_CPU_TYPES_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* TYPES */
typedef void (*cpu_stack_switch_callback_t)(void** from, void** to);

/* -------------------------------------------------------------------------------------------------------------- */
/* ERRORS */

#define CPU_STACK_OK        0
#define CPU_STACK_WIP       (-1)
#define CPU_STACK_ESIZE     (-2)
#define CPU_STACK_OVERFLOW  (-3)

#define CPU_STACK_MIN_SIZE     (18*4)


/* -------------------------------------------------------------------------------------------------------------- */
/* FUNCTIONS */

cpu_int_t cpu_stack_init(void* program_entry_p
                   , void* program_parameter
                   , uint8_t* stack_address
                   , cpu_int_t stack_size
                   , void* program_exit_function_p
                   , void** return_sp
            );

cpu_int_t cpu_stack_switch(void** from_stack_p, void** to_stack_p, cpu_stack_switch_callback_t on_success);

cpu_int_t cpu_stack_check(void* stack_addr, cpu_uint_t stack_size_nBytes, void* sp);

cpu_uint_t cpu_stack_remain(void* stack_addr, cpu_uint_t stack_size_nBytes, void* sp);

#endif /* INCLUDED_CPU_STACK_H */
