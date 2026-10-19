# AVR Embedded Systems

A progression of bare-metal C projects for the **Arduino Uno (ATmega328P)**, written without the Arduino framework: direct register access, hand-written drivers and layered firmware architecture.

Each project is a complete, standalone [PlatformIO](https://platformio.org/) project and builds on the lessons of the previous one.

| # | Project | Focus |
| --- | --- | --- |
| 1 | [GPIO, Timer and FSM](project-1-gpio-timer-fsm/) | Time base, GPIO, finite state machine, non-blocking firmware |
| 2 | UART Command Console | UART, reusable drivers, layered architecture, command console |
| 3 | Interrupt-Driven UART Event Stack | Interrupts, concurrency, ring buffers, event-driven firmware |
| 4 | Planned | Sensors and actuators |

Projects 2 and 3 are being added next.

## Principles

- Application code never touches registers; hardware access sits behind small drivers.
- Time is measured with a system tick, never with blocking delays.
- Interrupt handlers stay short, and the main loop does the interpreting.
- Logic with no hardware dependency is tested on the PC.

## Build

Open **one project folder** in VS Code (PlatformIO detects projects by `platformio.ini`), then:

```
pio run
pio run -t upload
```

Projects are self-contained and share no source files. Code reused from an earlier project is a copy, so each project builds exactly as it did when it was written.
