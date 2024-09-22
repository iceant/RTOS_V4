#ifndef INCLUDED_CPU_PRIVATE_H
#define INCLUDED_CPU_PRIVATE_H

#ifndef INCLUDED_CPU_FUNCTIONS_H
#include <cpu_functions.h>
#endif /*INCLUDED_CPU_FUNCTIONS_H*/

#ifndef INCLUDED_CPU_STACK_H
#include <cpu_stack.h>
#endif /*INCLUDED_CPU_STACK_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* STACK PRIVATE */

extern int             cpu_stack_switch_flag;
extern volatile void** cpu_stack_switch_from_p;
extern volatile void** cpu_stack_switch_to_p;
extern cpu_stack_switch_callback_t cpu_stack_switch_on_success_callback;
extern void cpu_stack_switch_on_success(void);


/* -------------------------------------------------------------------------------------------------------------- */
/* EXTERNAL LINKAGE */

extern void cpu_svc_register_init(void);


#endif /* INCLUDED_CPU_PRIVATE_H */
