#ifndef INCLUDED_SDK_ERROR_H
#define INCLUDED_SDK_ERROR_H

#ifndef INCLUDED_SDK_TYPES_H
#include <sdk_types.h>
#endif /*INCLUDED_SDK_TYPES_H*/

/* -------------------------------------------------------------------------------------------------------------- */
/*  */

typedef int sdk_err_t;

/* -------------------------------------------------------------------------------------------------------------- */
/* DEFINITIONS */

#define SDK_ERR_OK       0
#define SDK_ERR_ERROR    (-1)
#define SDK_ERR_NOMEM    (-2)
#define SDK_ERR_TIMEOUT  (-3)
#define SDK_ERR_FULL     (-4)
#define SDK_ERR_EMPTY    (-5)
#define SDK_ERR_PARAM    (-6)
#define SDK_ERR_RETRY    (-7)

#endif /* INCLUDED_SDK_ERROR_H */
