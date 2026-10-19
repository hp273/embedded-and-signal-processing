# Project 1: GPIO, Timer and FSM

Non-blocking embedded control system for the **Arduino Uno (ATmega328P)**, written in bare-metal C with direct register access and no Arduino framework.

**Focus:** time base, GPIO abstraction, finite state machine, non-blocking firmware.

## Behavior

In **RUN** mode, three LEDs blink independently at different rates, with no blocking delays:

| LED | Pin | Interval |
| --- | --- | --- |
| LED1 | D8 | 500 ms |
| LED2 | D9 | 1000 ms |
| LED3 | D10 | 2000 ms |

| Button | Pin | Effect |
| --- | --- | --- |
| Button 1 | D2 | RUN <-> PAUSE (LEDs freeze) |
| Button 2 | D3 | RUN <-> DIAGNOSTIC (reserved, LEDs freeze) |

DIAGNOSTIC is intentionally reserved in this project scope.

## Hardware

```
D8  -> 220 ohm -> LED1 -> GND
D9  -> 220 ohm -> LED2 -> GND
D10 -> 220 ohm -> LED3 -> GND

D2 -> push button -> GND
D3 -> push button -> GND
```

Buttons use the internal pull-ups: released = HIGH, pressed = LOW.

## Architecture

```
timer   1 ms system tick (Timer1, CTC mode), atomic 32-bit read
gpio    register-level pin access, Arduino pin numbers mapped to AVR ports
button  debounce + falling-edge detection -> events
system  finite state machine (RUN / PAUSE / DIAGNOSTIC)
led     non-blocking LED scheduling driven by the system state
main    initialization and super-loop
```

### State machine

```
RUN --button1--> PAUSE --button1--> RUN
RUN --button2--> DIAGNOSTIC --button2--> RUN
```

### Key ideas

- **Non-blocking timing:** each LED stores its last toggle time and is compared against `timer_millis()`. The loop never waits.
- **Atomic tick read:** the tick is 32 bits on an 8-bit CPU, so `timer_millis()` disables interrupts briefly during the copy and restores the previous `SREG`.
- **Debounce:** a button change is accepted only after the raw input has been stable for 20 ms.
- **Separation of concerns:** buttons produce events, the state machine decides, LEDs react to the state. No module reaches into another's internals.

## Build and run

Requires [PlatformIO](https://platformio.org/). Run these from inside this folder.

```
pio run
pio run -t upload
```

## Folder structure

```
project-1-gpio-timer-fsm/
├── README.md
├── platformio.ini
├── include/    gpio.h  timer.h  button.h  led.h  system.h
└── src/        main.c  gpio.c  timer.c  button.c  led.c  system.c
```
