#include <os_service.h>
#include <os_scheduler.h>
#include <cpu_svc.h>
#include <cpu.h>
/* -------------------------------------------------------------------------------------------------------------- */
/* SERVICES */

int os_service__svc__scheduler_method(cpu_uint_t * args, void* result){
    cpu_uint_t method_code = args[0]; /*要调用的方法代号*/
    switch (method_code) {
        case 0:{
            cpu_reboot();
            *(cpu_uint_t*)result = 0;
            break;
        }
        case 1:{
            /*os_scheduler_schedule*/
            (*(cpu_uint_t*)result) = os_scheduler_schedule();
            break;
        }
        case 2:{
            os_thread_t* thread_p =  (os_thread_t*)args[1];
            (*(cpu_uint_t*)result) = os_scheduler_yield(thread_p);
            break;
        }
        case 3:{
            os_thread_t* thread_p =  (os_thread_t*)args[1];
            (*(cpu_uint_t*)result) = os_scheduler_resume(thread_p);
            break;
        }
        case 4:{
            os_thread_t* thread_p =  (os_thread_t*)args[1];
            os_tick_t ticks = (os_tick_t)args[2];
            (*(cpu_uint_t*)result) = os_scheduler_delay(thread_p, ticks);
            break;
        }
        case 5:{
            os_waitobject_t * wait_object_p =  (os_waitobject_t*)args[1];
            os_thread_t* thread_p =  (os_thread_t*)args[2];
            os_tick_t ticks = (os_tick_t)args[3];
            (*(cpu_uint_t*)result) = os_waitobject_wait(wait_object_p, thread_p, ticks);
            break;
        }
        case 6:{
            os_waitobject_t * wait_object_p =  (os_waitobject_t*)args[1];
            (*(cpu_uint_t*)result) = os_waitobject_notify_one(wait_object_p);
            break;
        }
        case 7:{
            os_waitobject_t * wait_object_p =  (os_waitobject_t*)args[1];
            *(cpu_uint_t*)result = os_waitobject_notify_all(wait_object_p);
            break;
        }
        default:{
            break;
        }
    }
    
    return 0;
}


/* -------------------------------------------------------------------------------------------------------------- */
/* METHDOS */

void os_service_init(void){
    cpu_svc_register_function(1, os_service__svc__scheduler_method);
}

os_err_t os_service_schedule(void){
    if(cpu_in_privilege()){
        return os_scheduler_schedule();
    }else{
        cpu_svc_call1(1, 1);
    }
}

os_err_t os_service_yield(os_thread_t* thread){
    if(cpu_in_privilege()){
        return os_scheduler_yield(thread);
    }else{
        cpu_svc_call2(1, 2, thread);
    }
}

os_err_t os_service_resume(os_thread_t* thread){
    if(cpu_in_privilege()){
        return os_scheduler_resume(thread);
    }else{
        cpu_svc_call2(1, 3, thread);
    }
}

os_err_t os_service_delay(os_thread_t* thread, os_tick_t ticks){
    if(cpu_in_privilege()){
        return os_scheduler_delay(thread, ticks);
    }else{
        cpu_svc_call3(1, 4, thread, ticks);
    }
}

os_err_t os_service_systick(void){
    return os_scheduler_systick();
}


os_err_t os_service_wait(os_waitobject_t * wait_object, os_thread_t * thread, os_tick_t ticks){
    if(cpu_in_privilege()){
        return os_waitobject_wait(wait_object, thread, ticks);
    }else{
        cpu_svc_call4(1, 5, wait_object, thread, ticks);
    }
}

os_err_t os_service_notify(os_waitobject_t * wait_object){
    if(cpu_in_privilege()){
        return os_waitobject_notify_one(wait_object);
    }else{
        cpu_svc_call2(1, 6, wait_object);
    }
}

os_err_t os_service_notify_all(os_waitobject_t * wait_object){
    if(cpu_in_privilege()){
        return os_waitobject_notify_all(wait_object);
    }else{
        cpu_svc_call2(1, 7, wait_object);
    }
}

os_err_t os_service_reboot(void){
    if(cpu_in_privilege()){
        cpu_reboot();
        return 0;
    }else{
        cpu_svc_call1(1, 0);
    }
}

