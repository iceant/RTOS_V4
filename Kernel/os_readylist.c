#include <os_readylist.h>
#include <os_priority.h>
#include <os_list.h>
#include <os_thread.h>

/* -------------------------------------------------------------------------------------------------------------- */
/* STATIC */
static os_list_t os_readylist__table[OS_PRIORITY_MAX];

/* -------------------------------------------------------------------------------------------------------------- */
/* METHODS */

os_err_t os_readylist_init(void){
    os_size_t i;
    for(i=0; i<OS_PRIORITY_MAX; i++){
        OS_LIST_INIT(&os_readylist__table[i]);
    }
    return OS_ERR_OK;
}

os_err_t os_readylist_push_back(os_thread_t* thread){
    os_list_t * list = &os_readylist__table[thread->current_priority];
    if(OS_LIST_IS_EMPTY(list)){
        os_priority_mark(thread->current_priority);
    }
    OS_LIST_REMOVE(&thread->ready_node);
    OS_LIST_INSERT_BEFORE(list, &thread->ready_node);
    thread->state = OS_THREAD_STATE_READY;
    return OS_ERR_OK;
}

os_err_t os_readylist_push_front(os_thread_t* thread){
    os_list_t * list = &os_readylist__table[thread->current_priority];
    if(OS_LIST_IS_EMPTY(list)){
        os_priority_mark(thread->current_priority);
    }
    OS_LIST_REMOVE(&thread->ready_node);
    OS_LIST_INSERT_AFTER(list, &thread->ready_node);
    thread->state = OS_THREAD_STATE_READY;
    return OS_ERR_OK;
}

os_thread_t* os_readylist_pop(void){
    os_priority_t highest_priority = os_priority_highest();
    if(highest_priority>=OS_PRIORITY_MAX){
        return 0;
    }
    os_list_t * list = &os_readylist__table[highest_priority];
    if(OS_LIST_IS_EMPTY(list)){
        return 0;
    }
    os_list_node_t * node = OS_LIST_NEXT(list);
    OS_LIST_REMOVE(node);
    if(OS_LIST_IS_EMPTY(list)){
        os_priority_unmark(highest_priority);
    }
    return OS_LIST_CONTAINER(node, os_thread_t, ready_node);
}



