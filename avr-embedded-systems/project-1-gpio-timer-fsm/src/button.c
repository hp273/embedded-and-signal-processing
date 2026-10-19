#include "button.h"
#include "gpio.h"
#include "timer.h"
#include "system.h"
#include <stdint.h>

typedef struct
{
    uint8_t stable_state;
    uint8_t last_raw_state;
    uint32_t last_change_time;
} button_t;

/* Internal pull-up: released = HIGH, pressed = LOW. */
static button_t button1 = {GPIO_HIGH, GPIO_HIGH, 0U};
static button_t button2 = {GPIO_HIGH, GPIO_HIGH, 0U};

static void button_process(button_t *button,
                           uint8_t raw_state,
                           system_event_t press_event)
{
    uint32_t now = timer_millis();

    if (raw_state != button->last_raw_state)
    {
        button->last_raw_state = raw_state;
        button->last_change_time = now;
    }

    if ((now - button->last_change_time) >= BUTTON_DEBOUNCE_TIME_MS)
    {
        if (raw_state != button->stable_state)
        {
            button->stable_state = raw_state;

            /* Falling edge HIGH -> LOW means button press. */
            if (raw_state == GPIO_LOW)
                system_handle_event(press_event);
        }
    }
}

void button_init(void)
{
    gpio_set_pin_direction(BUTTON1_PIN, GPIO_INPUT);
    gpio_set_pin_direction(BUTTON2_PIN, GPIO_INPUT);

    gpio_enable_pullup(BUTTON1_PIN);
    gpio_enable_pullup(BUTTON2_PIN);

    button1.last_change_time = timer_millis();
    button2.last_change_time = timer_millis();
}

void button_task(void)
{
    button_process(&button1,
                   gpio_read_pin(BUTTON1_PIN),
                   EVENT_BUTTON1_PRESSED);

    button_process(&button2,
                   gpio_read_pin(BUTTON2_PIN),
                   EVENT_BUTTON2_PRESSED);
}
