# micro-ctl

**A lightweight, extensible command-line interface for interacting with and debugging microcontroller-based projects.**

`micro-ctl` aims to provide a unified interface between a host computer and microcontroller-based systems, enabling developers to interact with hardware, execute commands, inspect system state, and monitor applications without constantly modifying and reflashing firmware.

## Motivation

Embedded development often involves repeatedly modifying firmware, compiling, and flashing just to test individual hardware operations.

`micro-ctl` is an attempt to make that workflow more efficient.

The goal is to build a reusable host-side CLI that communicates with microcontrollers through a serial interface, allowing developers to interact with running firmware through a simple command-driven interface.

Rather than building another board-specific utility, the project is being developed with extensibility and hardware independence in mind.

## Current Status

**Early development — host-side prototype.**

Currently implemented:

- Interactive command-line interface
- Command parsing and dispatching
- Function-pointer-based command registration
- Modular command handling
- GPIO command interface
- Argument validation and error handling
- Reusable command parsing and dispatch architecture

The current GPIO commands perform host-side validation and demonstrate command execution flow. Actual hardware communication and GPIO control are not implemented yet.

## Planned Features

- [ ] Serial communication with microcontrollers
- [ ] Firmware-side command interpreter
- [ ] GPIO read, write, and mode configuration
- [ ] Peripheral interaction and testing
- [ ] Device status and diagnostic commands
- [ ] Runtime telemetry and monitoring
- [ ] Extensible command registration
- [ ] Support for multiple microcontroller platforms
- [ ] Interactive monitoring and visualization tools

## Architecture

The project is being developed around a modular architecture.

```text
micro-ctl/
├── include/
├── src/
│   ├── main.c
│   ├── commands.c
│   └── gpio/
│       ├── gpio_commands.c
│       ├── gpio_read.c
│       ├── gpio_write.c
│       └── gpio_mode.c
├── build/
└── Makefile
```

The intended communication model:

```text
        HOST COMPUTER
       ┌──────────────┐
       │  micro-ctl   │
       │              │
       │ Command Input│
       │ Parser       │
       │ Dispatcher   │
       └──────┬───────┘
              │
         Serial Interface
              │
       ┌──────▼───────┐
       │ Microcontroller│
       │               │
       │ Command Parser│
       │ Dispatcher    │
       │ Hardware APIs │
       └───────────────┘
```

The host-side interface and firmware are intended to remain independent components connected through a communication protocol.

## Design Goals

- **Modularity:** Keep command handling, parsing, transport, and hardware interaction separated.
- **Extensibility:** Make adding new commands and peripherals straightforward.
- **Portability:** Avoid coupling the host-side application to a particular microcontroller platform.
- **Simplicity:** Prefer a small, understandable implementation over unnecessary abstractions.
- **Reusability:** Design components that can be reused across embedded projects.

## Technology

- C
- Linux
- Make
- Serial communication (planned)

## Development

The project currently builds as a standalone host-side C application.

```bash
git clone https://github.com/gandharvak312/micro-ctl
cd micro-ctl
make
```

Run the application:

```bash
./build/micro
```

*Build instructions may evolve as the project develops.*

## Project Philosophy

The objective isn't simply to create a command-line wrapper around existing hardware APIs.

It's to understand and build the infrastructure that makes embedded systems easier to interact with, test, and debug.

This project is being developed incrementally, with an emphasis on understanding the underlying systems rather than hiding them behind abstractions.

---

**Status:** Work in progress.
