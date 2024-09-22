#include <cpu_svc.h>
#include <cpu_types.h>
/* -------------------------------------------------------------------------------------------------------------- */
/* UTILS */
#define ARRAY_SIZE(n) (sizeof(n)/sizeof((n)[0]))

/* -------------------------------------------------------------------------------------------------------------- */
/* STATIC */

static cpu_svc_function_t cpu_svc__functions[256];

/* -------------------------------------------------------------------------------------------------------------- */
/*  */
void cpu_svc_register_init(void){
    for(int i=0; i<ARRAY_SIZE(cpu_svc__functions); i++){
        cpu_svc__functions[i] = 0;
    }
}

cpu_svc_function_t cpu_svc_register_function(unsigned char code, cpu_svc_function_t function)
{
    cpu_svc_function_t fn = cpu_svc__functions[code];
    cpu_svc__functions[code] = function;
    return fn;
}

cpu_svc_function_t cpu_svc_get_function(unsigned char code){
    return cpu_svc__functions[code];
}


