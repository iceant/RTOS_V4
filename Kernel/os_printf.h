#ifndef INCLUDED_OS_PRINTF_H
#define INCLUDED_OS_PRINTF_H

#ifndef INCLUDED_STDARG_H
#define INCLUDED_STDARG_H
#include <stdarg.h>
#endif /*INCLUDED_STDARG_H*/

#ifndef INCLUDED_OS_TYPES_H
#include <os_types.h>
#endif /*INCLUDED_OS_TYPES_H*/



/* -------------------------------------------------------------------------------------------------------------- */
/*  */

int os_printf(const char* fmt, ...);



#endif /* INCLUDED_OS_PRINTF_H */
