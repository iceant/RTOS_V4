#include <os_kernel.h>
#include <os_scheduler.h>
#include <cpu.h>
#include <os_idle.h>
#include <os_readylist.h>
#include <os_priority.h>
#include <os_timewheel.h>

os_err_t os_kernel_init(void)
{
    os_memory_init();
    
    cpu_init();
    
    os_priority_init();
    os_readylist_init();
    os_timewheel_init();
    
    os_scheduler_init();
    
    os_service_init();
    
    os_idle_startup();
    
    return OS_ERR_OK;
}

os_err_t os_kernel_startup(void)
{
    return os_scheduler_startup();
}

