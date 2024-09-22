#ifndef INCLUDED_OS_ERROR_H
#define INCLUDED_OS_ERROR_H

#ifndef INCLUDED_OS_TYPES_H
#include <os_types.h>
#endif /*INCLUDED_OS_TYPES_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/* TYPES */

typedef os_int_t os_err_t;

/* -------------------------------------------------------------------------------------------------------------- */
/* CONSTANTS */

#define OS_ERR_OK       0
#define OS_ERR_ERROR    (-1)
#define OS_ERR_NOMEM    (-2)
#define OS_ERR_TIMEOUT  (-3)
#define OS_ERR_FULL     (-4)
#define OS_ERR_EMPTY    (-5)
#define OS_ERR_PARAM    (-6)
#define OS_ERR_RETRY    (-7)


#endif /* INCLUDED_OS_ERROR_H */
