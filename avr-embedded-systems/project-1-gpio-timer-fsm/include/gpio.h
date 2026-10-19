#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>

typedef enum
{
    GPIO_INPUT = 0,
    GPIO_OUTPUT
} gpio_direction_t;

typedef enum
{
    GPIO_LOW = 0,
    GPIO_HIGH
} gpio_state_t;

/* Arduino Uno digital/analog pin numbers. */
#define D0   0
#define D1   1
#define D2   2
#define D3   3
#define D4   4
#define D5   5
#define D6   6
#define D7   7
#define D8   8
#define D9   9
#define D10 10
#define D11 11
#define D12 12
#define D13 13
#define A0  14
#define A1  15
#define A2  16
#define A3  17
#define A4  18
#define A5  19

void gpio_set_pin_direction(uint8_t pin, gpio_direction_t direction);
void gpio_write_pin(uint8_t pin, gpio_state_t state);
void gpio_toggle_pin(uint8_t pin);
gpio_state_t gpio_read_pin(uint8_t pin);
void gpio_enable_pullup(uint8_t pin);

#endif /* GPIO_H */
