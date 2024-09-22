#ifndef INCLUDED_OS_TICK_H
#define INCLUDED_OS_TICK_H

#ifndef INCLUDED_OS_TYPES_H
#include <os_types.h>
#endif /*INCLUDED_OS_TYPES_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* TYPES */
typedef os_uint_t os_tick_t;

/* -------------------------------------------------------------------------------------------------------------- */
/* METHOD */

os_tick_t os_tick_from_millisecond(os_uint_t ms);


#endif /* INCLUDED_OS_TICK_H */
