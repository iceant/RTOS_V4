#ifndef INCLUDED_OS_IDLE_H
#define INCLUDED_OS_IDLE_H

typedef void (*os_idle_action_t)(void);

void os_idle_startup(void);

void os_idle_set_action(os_idle_action_t action);

#endif /* INCLUDED_OS_IDLE_H */
