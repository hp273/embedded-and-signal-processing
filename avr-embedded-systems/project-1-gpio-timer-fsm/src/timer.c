#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/* Private to this file: nothing outside timer.c touches this directly. */
static volatile uint32_t system_tick = 0U;

/* Timer1 Compare Match A ISR: keep application logic out of ISR. */
ISR(TIMER1_COMPA_vect)
{
    system_tick++;
}

uint32_t timer_millis(void)
{
    uint32_t tick_copy;
    uint8_t sreg = SREG;   /* remember whether interrupts were enabled */

    cli();
    tick_copy = system_tick;   /* 4-byte read, now uninterruptible */
    SREG = sreg;                /* restore prior interrupt state, don't blindly sei() */

    return tick_copy;
}

/*
 * Timer1 CTC configuration:
 * F_CPU = 16 MHz
 * Prescaler = 64
 * Timer clock = 250 kHz
 * 250 counts = 1 ms
 * OCR1A = 249
 */
void timer_init(void)
{
    cli();

    TCCR1A = 0U;
    TCCR1B = 0U;
    TCNT1  = 0U;

    /* CTC mode. */
    TCCR1B |= (1U << WGM12);

    /* 1 ms period. */
    OCR1A = 249U;

    /* Enable Compare Match A interrupt. */
    TIMSK1 |= (1U << OCIE1A);

    /* Start Timer1 with prescaler 64. */
    TCCR1B |= (1U << CS11) | (1U << CS10);

    sei();
}
