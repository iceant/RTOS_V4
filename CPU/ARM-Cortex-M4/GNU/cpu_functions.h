#ifndef INCLUDED_CPU_FUNCTIONS_H
#define INCLUDED_CPU_FUNCTIONS_H

#ifndef INCLUDED_C_COMPILER_H
#include <c_compiler.h>
#endif /*INCLUDED_C_COMPILER_H*/

#ifndef INCLUDED_CPU_TYPES_H
#include <cpu_types.h>
#endif /*INCLUDED_CPU_TYPES_H*/


/* -------------------------------------------------------------------------------------------------------------- */
/* FUNCTIONS */

#define cpu_svc(sNum)   __asm volatile("SVC %0" ::"M" (sNum))

#define cpu_nop()       __asm volatile("nop")

C_STATIC_FORCE_INLINE void cpu_enable_irq(void)
{
    __asm volatile ("cpsie i" : : : "memory");
}

C_STATIC_FORCE_INLINE void cpu_disable_irq(void)
{
    __asm volatile ("cpsid i" : : : "memory");
}

C_STATIC_FORCE_INLINE cpu_uint_t cpu_ldrexw(volatile cpu_uint_t * addr)
{
    cpu_uint_t result;
    __asm volatile ("ldrex %0, %1" : "=r" (result) : "Q" (*addr) );
    return(result);
}

C_STATIC_FORCE_INLINE cpu_uint_t cpu_strexw(cpu_uint_t value, volatile cpu_uint_t * addr)
{
    cpu_uint_t result;
    __asm volatile("strex %0, %2, %1":"=&r"(result), "=Q"(*addr):"r"(value));
    return result;
}

C_STATIC_FORCE_INLINE void cpu_clrex(void){
    __asm volatile("clrex":::"memory");
}

C_STATIC_FORCE_INLINE void cpu_dmb(void){
    __asm volatile("dmb 0x0F":::"memory");
}

C_STATIC_FORCE_INLINE void cpu_isb(void){
    __asm volatile("isb 0x0F":::"memory");
}

C_STATIC_FORCE_INLINE void cpu_dsb(void){
    __asm volatile("dsb 0x0F":::"memory");
}

C_STATIC_FORCE_INLINE void cpu_set_primask(cpu_uint_t priMask)
{
    __asm volatile ("MSR primask, %0"::"r" (priMask):"memory");
}

C_STATIC_FORCE_INLINE cpu_uint_t cpu_get_primask(void)
{
    cpu_uint_t result;
    __asm volatile ("MRS %0, primask":"=r"(result));
    return (result);
}

C_STATIC_FORCE_INLINE cpu_uint_t cpu_get_basepri(void){
    cpu_uint_t result;
    __asm volatile("MRS %0, basepri":"=r"(result));
    return (result);
}

C_STATIC_FORCE_INLINE void cpu_set_basepri(cpu_uint_t basePri){
    __asm volatile("MSR basepri, %0"::"r"(basePri):"memory");
}

C_STATIC_FORCE_INLINE cpu_uint_t cpu_get_ipsr(void){
    cpu_uint_t result;
    __asm volatile("MRS %0, ipsr":"=r"(result)::);
    return (result);
}

C_STATIC_FORCE_INLINE cpu_uint_t cpu_get_control(void){
    cpu_uint_t result;
    __asm volatile("MRS %0, control":"=r"(result));
    return (result);
}

C_STATIC_FORCE_INLINE void cpu_set_control(cpu_uint_t control){
    __asm volatile("MSR control, %0"::"r"(control):"memory");
}

C_STATIC_FORCE_INLINE uint8_t cpu_clz(uint32_t value){
    cpu_uint_t result;
    __asm volatile ("CLZ %0, %1":"=r"(result):"r"(value));
    return (result & 0xFF);
}

C_STATIC_FORCE_INLINE void cpu_reboot(void){
    volatile cpu_uint_t *aircr = (volatile cpu_uint_t*)0xE000ED0C;
    *aircr = (0x05FA << 16) | 0x1 << 2;
    while (1) { } // should be unreachable
}

C_STATIC_FORCE_INLINE void cpu_set_msp(cpu_uint_t msp){
    __asm volatile("MSR msp, %0"::"r"(msp):"memory");
}
/* -------------------------------------------------------------------------------------------------------------- */
/*  */

#define cpu_svc_call0(code) do{ \
    register cpu_uint_t r0 asm("r0"); \
    __asm volatile(             \
            "SVC "#code         \
            :::"memory"        \
            );                  \
    return r0;                  \
}while(0)

#define cpu_svc_call1(code, arg1) do{ \
    register cpu_uint_t r0 asm("r0") = (cpu_uint_t)arg1; \
    __asm volatile(                                     \
            "SVC "#code                                 \
            :: "r" (r0)                                 \
            : "memory"                                  \
            );                                          \
    return r0;                                          \
}while(0)

#define cpu_svc_call2(code, arg1, arg2) do{ \
    register cpu_uint_t r0 asm("r0") = (cpu_uint_t)arg1; \
    register cpu_uint_t r1 asm("r1") = (cpu_uint_t)arg2; \
    __asm volatile(                                     \
            "SVC "#code                                 \
            :: "r" (r0), "r"(r1)                        \
            : "memory"                                  \
            );                                          \
    return r0;                                          \
}while(0)

#define cpu_svc_call3(code, arg1, arg2, arg3) do{ \
    register cpu_uint_t r0 asm("r0") = (cpu_uint_t)arg1; \
    register cpu_uint_t r1 asm("r1") = (cpu_uint_t)arg2; \
    register cpu_uint_t r2 asm("r2") = (cpu_uint_t)arg3; \
    __asm volatile(                                     \
            "SVC "#code                                 \
            :: "r" (r0), "r"(r1), "r"(r2)               \
            : "memory"                                  \
            );                                          \
    return r0;                                          \
}while(0)

#define cpu_svc_call4(code, arg1, arg2, arg3, arg4) do{ \
    register cpu_uint_t r0 asm("r0") = (cpu_uint_t)arg1; \
    register cpu_uint_t r1 asm("r1") = (cpu_uint_t)arg2; \
    register cpu_uint_t r2 asm("r2") = (cpu_uint_t)arg3; \
    register cpu_uint_t r3 asm("r3") = (cpu_uint_t)arg4; \
    __asm volatile(                                     \
            "SVC "#code                                 \
            :: "r" (r0), "r" (r1), "r" (r2), "r" (r3)   \
            : "memory"                                  \
            );                                          \
    return r0;                                          \
}while(0)



#endif /* INCLUDED_CPU_FUNCTIONS_H */
