#ifndef LED_H
#define LED_H
#include <stdint.h>

#define LED1_PIN D8
#define LED2_PIN D9
#define LED3_PIN D10

void led_init(void);
void led_task(void);

#endif /* LED_H */
