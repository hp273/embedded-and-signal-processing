#include "timer.h"
#include "system.h"
#include "led.h"
#include "button.h"

int main(void)
{
    timer_init();
    system_init();
    led_init();
    button_init();

    while (1)
    {
        button_task();
        led_task();
    }
}
