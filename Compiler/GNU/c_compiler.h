#ifndef INCLUDED_C_COMPILER_H
#define INCLUDED_C_COMPILER_H

#define C_STATIC_FORCE_INLINE       static inline __attribute__((always_inline))

#define C_SECTION(n)                __attribute__((section(#n)))

#define C_ALIGNED(n)                __attribute__((aligned(n)))

#define C_WEAK                      __attribute__((weak))

#define C_PACKED_STRUCT             __packed struct

#define C_PACKED_UNION             __packed union

#define C_ASM                      __asm__

#endif /* INCLUDED_C_COMPILER_H */
