#ifndef INCLUDED_OS_KERNEL_H
#define INCLUDED_OS_KERNEL_H

#ifndef INCLUDED_OS_TYPES_H
#include <os_types.h>
#endif /*INCLUDED_OS_TYPES_H*/

#ifndef INCLUDED_OS_ERROR_H
#include <os_error.h>
#endif /*INCLUDED_OS_ERROR_H*/

#ifndef INCLUDED_OS_MEMORY_H
#include <os_memory.h>
#endif /*INCLUDED_OS_MEMORY_H*/

#ifndef INCLUDED_OS_MACROS_H
#include <os_macros.h>
#endif /*INCLUDED_OS_MACROS_H*/

#ifndef INCLUDED_OS_SERVICE_H
#include <os_service.h>
#endif /*INCLUDED_OS_SERVICE_H*/

#ifndef INCLUDED_OS_INTERRUPT_H
#include <os_interrupt.h>
#endif /*INCLUDED_OS_INTERRUPT_H*/

#ifndef INCLUDED_OS_SEM_H
#include <os_sem.h>
#endif /*INCLUDED_OS_SEM_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* METHOD */

os_err_t os_kernel_init(void);

os_err_t os_kernel_startup(void);


#endif /* INCLUDED_OS_KERNEL_H */
