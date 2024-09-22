#ifndef INCLUDED_SDK_TYPES_H
#define INCLUDED_SDK_TYPES_H

#ifndef INCLUDED_STDINT_H
#define INCLUDED_STDINT_H
#include <stdint.h>
#endif /*INCLUDED_STDINT_H*/

#ifndef INCLUDED_STDDEF_H
#define INCLUDED_STDDEF_H
#include <stddef.h>
#endif /*INCLUDED_STDDEF_H*/

#ifndef INCLUDED_STDBOOL_H
#define INCLUDED_STDBOOL_H
#include <stdbool.h>
#endif /*INCLUDED_STDBOOL_H*/

#ifndef INCLUDED_INTTYPES_H
#define INCLUDED_INTTYPES_H
#include <inttypes.h>
#endif /*INCLUDED_INTTYPES_H*/

#ifndef INCLUDED_CTYPE_H
#define INCLUDED_CTYPE_H
#include <ctype.h>
#endif /*INCLUDED_CTYPE_H*/

#ifndef INCLUDED_C_COMPILER_H
#include <c_compiler.h>
#endif /*INCLUDED_C_COMPILER_H*/

#ifndef INCLUDED_SDK_DEFINITION_H
#include <sdk_definition.h>
#endif /*INCLUDED_SDK_DEFINITION_H*/


/* -------------------------------------------------------------------------------------------------------------- */
/* TYPES */

typedef size_t sdk_size_t;

#define sdk_bool_t  bool
#define SDK_TRUE    true
#define SDK_FALSE   false

#endif /* INCLUDED_SDK_TYPES_H */
