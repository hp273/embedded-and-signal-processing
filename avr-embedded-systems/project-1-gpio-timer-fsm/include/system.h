#ifndef SYSTEM_H
#define SYSTEM_H
#include <stdint.h>

typedef enum
{
    MODE_RUN = 0,
    MODE_PAUSE,
    MODE_DIAGNOSTIC
} system_state_t;

typedef enum
{
    EVENT_NONE = 0,
    EVENT_BUTTON1_PRESSED,
    EVENT_BUTTON2_PRESSED
} system_event_t;

void system_init(void);
void system_handle_event(system_event_t event);
system_state_t system_get_state(void);

#endif /* SYSTEM_H */
