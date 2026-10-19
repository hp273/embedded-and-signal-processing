#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>

/* Initialize Timer1 for a 1 ms system tick. */
void timer_init(void);

/*
 * Atomically read the current system tick (milliseconds since timer_init).
 * system_tick is 32 bits and this is an 8-bit CPU, so a plain read can be
 * torn by the Timer1 ISR mid-copy. This function briefly disables
 * interrupts to guarantee a whole, consistent value.
 */
uint32_t timer_millis(void);

#endif /* TIMER_H */
