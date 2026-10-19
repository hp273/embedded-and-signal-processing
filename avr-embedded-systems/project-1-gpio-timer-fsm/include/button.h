#ifndef BUTTON_H
#define BUTTON_H
#include <stdint.h>

#define BUTTON1_PIN D2
#define BUTTON2_PIN D3
#define BUTTON_DEBOUNCE_TIME_MS 20U

void button_init(void);
void button_task(void);

#endif /* BUTTON_H */
