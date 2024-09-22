#ifndef INCLUDED_CPU_ATOMIC_H
#define INCLUDED_CPU_ATOMIC_H

#ifndef INCLUDED_CPU_FUNCTIONS_H
#include <cpu_functions.h>
#endif /*INCLUDED_CPU_FUNCTIONS_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/*  */

typedef volatile cpu_uint_t cpu_atomic_t;

C_STATIC_FORCE_INLINE void cpu_atomic_init(cpu_atomic_t * atomic){
    *atomic= 0;
}

C_STATIC_FORCE_INLINE cpu_uint_t cpu_atomic_add_return(cpu_atomic_t* v, cpu_uint_t i){
    cpu_uint_t tmp;
    cpu_uint_t result;
    cpu_dmb();
    do{
        result = cpu_ldrexw(v);
        result = result + i;
        tmp = cpu_strexw(result, v);
    }while(tmp!=0);
    cpu_dmb();
    return result;
}

C_STATIC_FORCE_INLINE cpu_uint_t cpu_atomic_sub_return(cpu_atomic_t* v, cpu_uint_t i){
    cpu_uint_t tmp;
    cpu_uint_t result;
    cpu_dmb();
    do{
        result = cpu_ldrexw(v);
        result = result - i;
        tmp = cpu_strexw(result, v);
    }while(tmp!=0);
    cpu_dmb();
    return result;
}

/* return old value */
C_STATIC_FORCE_INLINE cpu_uint_t cpu_atomic_cmpxchg(cpu_atomic_t* v, cpu_uint_t old_value, cpu_uint_t new_value){
    cpu_uint_t tmp;
    cpu_uint_t result;
    cpu_dmb();
    do{
        result = cpu_ldrexw(v);
        tmp = 0;
        if(result==old_value){
            tmp = cpu_strexw(new_value, v);
        }
    }while(tmp!=0);
    cpu_dmb();
    return result;
}

C_STATIC_FORCE_INLINE cpu_uint_t cpu_atomic_inc(cpu_atomic_t* atomic){
    return cpu_atomic_add_return(atomic, 1);
}

C_STATIC_FORCE_INLINE cpu_uint_t cpu_atomic_dec(cpu_atomic_t* atomic){
    return cpu_atomic_sub_return(atomic, 1);
}

C_STATIC_FORCE_INLINE cpu_uint_t cpu_atomic_get(cpu_atomic_t* atomic){
    cpu_dmb();
    return cpu_ldrexw(atomic);
}

#endif /* INCLUDED_CPU_ATOMIC_H */
