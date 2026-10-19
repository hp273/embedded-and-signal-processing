#include "system.h"

static system_state_t current_state;

void system_init(void)
{
    current_state = MODE_RUN;
}

system_state_t system_get_state(void)
{
    return current_state;
}

/*
 * State transitions:
 * RUN:
 *   BUTTON1 -> PAUSE
 *   BUTTON2 -> DIAGNOSTIC
 * PAUSE:
 *   BUTTON1 -> RUN
 * DIAGNOSTIC:
 *   BUTTON2 -> RUN
 */
void system_handle_event(system_event_t event)
{
    switch (current_state)
    {
        case MODE_RUN:
            if (event == EVENT_BUTTON1_PRESSED)
                current_state = MODE_PAUSE;
            else if (event == EVENT_BUTTON2_PRESSED)
                current_state = MODE_DIAGNOSTIC;
            break;

        case MODE_PAUSE:
            if (event == EVENT_BUTTON1_PRESSED)
                current_state = MODE_RUN;
            break;

        case MODE_DIAGNOSTIC:
            if (event == EVENT_BUTTON2_PRESSED)
                current_state = MODE_RUN;
            break;

        default:
            current_state = MODE_RUN;
            break;
    }
}
