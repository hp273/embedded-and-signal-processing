#include "led.h"
#include "gpio.h"
#include "timer.h"
#include "system.h"
#include <stdint.h>

typedef struct
{
    uint32_t last_toggle_time;
    uint32_t interval_ms;
    uint8_t state;
} led_t;

static led_t led1 = {0U, 500U, 0U};
static led_t led2 = {0U, 1000U, 0U};
static led_t led3 = {0U, 2000U, 0U};

static void led1_toggle(void)
{
    gpio_toggle_pin(LED1_PIN);
    led1.state ^= 1U;
}

static void led2_toggle(void)
{
    gpio_toggle_pin(LED2_PIN);
    led2.state ^= 1U;
}

static void led3_toggle(void)
{
    gpio_toggle_pin(LED3_PIN);
    led3.state ^= 1U;
}

void led_init(void)
{
    gpio_set_pin_direction(LED1_PIN, GPIO_OUTPUT);
    gpio_set_pin_direction(LED2_PIN, GPIO_OUTPUT);
    gpio_set_pin_direction(LED3_PIN, GPIO_OUTPUT);

    gpio_write_pin(LED1_PIN, GPIO_LOW);
    gpio_write_pin(LED2_PIN, GPIO_LOW);
    gpio_write_pin(LED3_PIN, GPIO_LOW);

    led1.last_toggle_time = timer_millis();
    led2.last_toggle_time = timer_millis();
    led3.last_toggle_time = timer_millis();
}

/* Non-blocking LED scheduler. */
void led_task(void)
{
    uint32_t now = timer_millis();

    switch (system_get_state())
    {
        case MODE_RUN:
            if ((now - led1.last_toggle_time) >= led1.interval_ms)
            {
                led1_toggle();
                led1.last_toggle_time = now;
            }

            if ((now - led2.last_toggle_time) >= led2.interval_ms)
            {
                led2_toggle();
                led2.last_toggle_time = now;
            }

            if ((now - led3.last_toggle_time) >= led3.interval_ms)
            {
                led3_toggle();
                led3.last_toggle_time = now;
            }
            break;

        case MODE_PAUSE:
            /* LEDs remain frozen. */
            break;

        case MODE_DIAGNOSTIC:
            /* Diagnostic pattern reserved for this project scope. */
            break;

        default:
            break;
    }
}
