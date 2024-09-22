#ifndef INCLUDED_CPU_EXCEPTION_H
#define INCLUDED_CPU_EXCEPTION_H

/* -------------------------------------------------------------------------------------------------------------- */
/*  */

typedef void (*cpu_exception_handler_t)(void*);

/* -------------------------------------------------------------------------------------------------------------- */
/* METHODS */

void cpu_exception_set_handler(cpu_exception_handler_t handler);

void cpu_exception_handle_exception(void*);

#endif /* INCLUDED_CPU_EXCEPTION_H */
