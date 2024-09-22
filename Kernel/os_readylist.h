#ifndef INCLUDED_OS_READYLIST_H
#define INCLUDED_OS_READYLIST_H

#ifndef INCLUDED_OS_TYPES_H
#include <os_types.h>
#endif /*INCLUDED_OS_TYPES_H*/

#ifndef INCLUDED_OS_ERROR_H
#include <os_error.h>
#endif /*INCLUDED_OS_ERROR_H*/

#ifndef INCLUDED_OS_THREAD_H
#include <os_thread.h>
#endif /*INCLUDED_OS_THREAD_H*/



/* -------------------------------------------------------------------------------------------------------------- */
/* METHOD */

os_err_t os_readylist_init(void);


os_thread_t* os_readylist_pop(void);

os_err_t os_readylist_push_front(os_thread_t* thread);

os_err_t os_readylist_push_back(os_thread_t* thread);

#endif /* INCLUDED_OS_READYLIST_H */
