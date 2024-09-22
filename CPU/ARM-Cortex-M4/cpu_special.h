#ifndef INCLUDED_CPU_SPECIAL_H
#define INCLUDED_CPU_SPECIAL_H

#ifndef INCLUDED_CPU_FUNCTIONS_H
#include <cpu_functions.h>
#endif /*INCLUDED_CPU_FUNCTIONS_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* METHODS */


C_STATIC_FORCE_INLINE int cpu_in_privilege(void){
    if(cpu_get_ipsr()!=0) return 1;
    if((cpu_get_control() & 0x01)==0) return 1;
    return 0;
}

C_STATIC_FORCE_INLINE int cpu_in_interrupt(void){
    return (cpu_get_ipsr()!=0)?1:0;
}


#endif /* INCLUDED_CPU_SPECIAL_H */
