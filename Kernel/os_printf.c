#include <os_printf.h>
#include <stdio.h>

/* -------------------------------------------------------------------------------------------------------------- */
/*  */
static os_bool_t os_printf__flag = OS_FALSE;
static char os_printf__buffer[OS_PRINTF_BUFFER_SIZE];
/* -------------------------------------------------------------------------------------------------------------- */
/*  */

int os_printf(const char* fmt, ...){
    if(os_printf__flag == OS_TRUE){
        return 0;
    }
    os_printf__flag = OS_TRUE;
    size_t size;
    va_list ap;
    va_start(ap, fmt);
    size = vsnprintf(os_printf__buffer, OS_PRINTF_BUFFER_SIZE, fmt, ap);
    va_end(ap);
    if(size<OS_PRINTF_BUFFER_SIZE){
        os_printf__buffer[size]='\0';
        printf("%s", os_printf__buffer);
    }
    os_printf__flag = OS_FALSE;
    return (int)size;
}

