#ifndef INCLUDED_CPU_FUNCTIONS_H
#define INCLUDED_CPU_FUNCTIONS_H

/* -------------------------------------------------------------------------------------------------------------- */
/* CPU TYPES */
#ifndef INCLUDED_CPU_TYPES_H
#include <cpu_types.h>
#endif /*INCLUDED_CPU_TYPES_H*/

#ifndef INCLUDED_C_COMPILER_H
#include <c_compiler.h>
#endif /*INCLUDED_C_COMPILER_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* COMPILER INTERNAL FUNCTIONS */

//extern uint8_t __clz(cpu_uint_t);
//extern void __clrex(void);
//extern void __disable_irq(void);
//extern void __enable_irq(void);
//extern void __disable_fiq(void);
//extern void __enable_fiq(void);
//extern cpu_uint_t __ldrex(volatile void*);
//extern void __nop(void);
//extern cpu_uint_t __rbit(cpu_uint_t);
//extern cpu_uint_t __rev(cpu_uint_t);
//extern cpu_uint_t __ror(cpu_uint_t val, cpu_uint_t shift);
//extern cpu_int_t __ssat(cpu_int_t val, cpu_uint_t sat);
//extern void __sev(void);
//extern cpu_int_t __strex(cpu_uint_t val, volatile void* ptr);
//extern cpu_int_t __strt(cpu_uint_t val, const volatile void* ptr);
//extern cpu_int_t __usat(cpu_uint_t val, cpu_uint_t sat);
//extern void __wfe(void);
//extern void __wfi(void);
//extern void __breakpoint(int val);
//extern void __schedule_barrier(void);
//extern void __dmb(unsigned char);
//extern void __isb(unsigned char);
//extern void __dsb(unsigned char);


/* -------------------------------------------------------------------------------------------------------------- */
/*  */

#define cpu_svc(n) __asm{SVC n}

#define cpu_ldrexw      __ldrex
#define cpu_strexw      __strex
//#define cpu_disable_irq __disable_irq
//#define cpu_enable_irq  __enable_irq

#define cpu_isb() __isb(0xf)

#define cpu_dsb() __dsb(0xf)

#define cpu_dmb() __dmb(0xf)

#define cpu_clz   __clz

/* -------------------------------------------------------------------------------------------------------------- */
/* FUNCTIONS */

C_STATIC_FORCE_INLINE void cpu_disable_irq(void){
    __asm {
        CPSID I
    }
}

C_STATIC_FORCE_INLINE void cpu_enable_irq(void){
    __asm {
            CPSIE I
    }
}

C_STATIC_FORCE_INLINE cpu_uint_t cpu_get_ipsr(void){
    register cpu_uint_t __regIPSR __asm("ipsr");
    return (__regIPSR);
}

C_STATIC_FORCE_INLINE cpu_uint_t cpu_get_primask(void){
    register cpu_uint_t __regPriMask __asm("primask");
    return (__regPriMask);
}

C_STATIC_FORCE_INLINE void cpu_set_primask(cpu_uint_t priMask){
    register cpu_uint_t __regPriMask __asm("primask");
    __regPriMask = priMask;
}

C_STATIC_FORCE_INLINE cpu_uint_t cpu_get_basepri(void){
    register cpu_uint_t __regBasePri __asm("basepri");
    return (__regBasePri);
}

C_STATIC_FORCE_INLINE void cpu_set_basepri(cpu_uint_t basePri){
    register cpu_uint_t __regBasePri __asm("basepri");
    __regBasePri = (basePri & 0xFFu);
}

C_STATIC_FORCE_INLINE cpu_uint_t cpu_get_control(void){
    register cpu_uint_t __regControl __asm("control");
    return __regControl;
}

C_STATIC_FORCE_INLINE void cpu_reboot(void){
    volatile cpu_uint_t *aircr = (volatile cpu_uint_t*)0xE000ED0C;
    *aircr = (0x05FA << 16) | 0x1 << 2;
    while (1) { } // should be unreachable
}

/* -------------------------------------------------------------------------------------------------------------- */
/*  */

#define cpu_svc_call0(code) do{ \
    register cpu_uint_t r0 __asm("r0"); \
    __asm {SVC code}            \
    return r0;                  \
}while(0)

#define cpu_svc_call1(code, arg1) do{ \
    register cpu_uint_t result;       \
    __asm {                           \
        SVC code, {r0=arg1}, {result=r0} \
    }                                 \
    return result;                    \
}while(0)

#define cpu_svc_call2(code, arg1, arg2) do{ \
    register cpu_uint_t result;             \
    __asm {                                 \
        SVC code, {r0=arg1, r1=arg2}, {result=r0} \
    }                                       \
    return result;                          \
}while(0)

#define cpu_svc_call3(code, arg1, arg2, arg3) do{ \
    register cpu_uint_t result;                   \
    __asm {                                       \
        SVC code, {r0=arg1, r1=arg2, r2=arg3}, {result=r0} \
    }                                             \
    return result;                                \
}while(0)

#define cpu_svc_call4(code, arg1, arg2, arg3, arg4) do{ \
    register cpu_uint_t result;                         \
    __asm {                                             \
        SVC code, {r0=arg1, r1=arg2, r2=arg3, r3=arg4}, {result=r0} \
    }                                                   \
    return result;                                      \
}while(0)




#endif /* INCLUDED_CPU_FUNCTIONS_H */
