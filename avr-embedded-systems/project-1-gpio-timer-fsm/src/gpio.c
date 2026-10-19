#include "gpio.h"
#include <avr/io.h>

/* Return DDR register for an Arduino Uno pin. */
static volatile uint8_t *gpio_ddr(uint8_t pin)
{
    if (pin <= D7) return &DDRD;
    if (pin <= D13) return &DDRB;
    return &DDRC;
}

/* Return PORT register for an Arduino Uno pin. */
static volatile uint8_t *gpio_port(uint8_t pin)
{
    if (pin <= D7) return &PORTD;
    if (pin <= D13) return &PORTB;
    return &PORTC;
}

/* Return PIN register for an Arduino Uno pin. */
static volatile uint8_t *gpio_pin_register(uint8_t pin)
{
    if (pin <= D7) return &PIND;
    if (pin <= D13) return &PINB;
    return &PINC;
}

/* Convert Arduino pin number to AVR port bit number. */
static uint8_t gpio_bit(uint8_t pin)
{
    if (pin <= D7) return pin;
    if (pin <= D13) return pin - D8;
    return pin - A0;
}

void gpio_set_pin_direction(uint8_t pin, gpio_direction_t direction)
{
    volatile uint8_t *ddr = gpio_ddr(pin);
    uint8_t bit = gpio_bit(pin);

    if (direction == GPIO_OUTPUT)
        *ddr |= (1U << bit);
    else
        *ddr &= ~(1U << bit);
}

void gpio_write_pin(uint8_t pin, gpio_state_t state)
{
    volatile uint8_t *port = gpio_port(pin);
    uint8_t bit = gpio_bit(pin);

    if (state == GPIO_HIGH)
        *port |= (1U << bit);
    else
        *port &= ~(1U << bit);
}

void gpio_toggle_pin(uint8_t pin)
{
    volatile uint8_t *port = gpio_port(pin);
    uint8_t bit = gpio_bit(pin);
    *port ^= (1U << bit);
}

gpio_state_t gpio_read_pin(uint8_t pin)
{
    volatile uint8_t *pin_reg = gpio_pin_register(pin);
    uint8_t bit = gpio_bit(pin);

    return ((*pin_reg & (1U << bit)) != 0U) ? GPIO_HIGH : GPIO_LOW;
}

void gpio_enable_pullup(uint8_t pin)
{
    volatile uint8_t *port = gpio_port(pin);
    uint8_t bit = gpio_bit(pin);
    *port |= (1U << bit);
}
