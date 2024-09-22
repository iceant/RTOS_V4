#ifndef INCLUDED_CPU_SVC_H
#define INCLUDED_CPU_SVC_H

#ifndef INCLUDED_CPU_TYPES_H
#include <cpu_types.h>
#endif /*INCLUDED_CPU_TYPES_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* TYPES */

typedef int (*cpu_svc_function_t)(cpu_uint_t * args, void* result);

/* -------------------------------------------------------------------------------------------------------------- */
/*  */

cpu_svc_function_t cpu_svc_register_function(unsigned char code, cpu_svc_function_t function);

cpu_svc_function_t cpu_svc_get_function(unsigned char code);


#endif /* INCLUDED_CPU_SVC_H */
