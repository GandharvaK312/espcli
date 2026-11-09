# espcli

**A lightweight command-line interface for embedded systems, built in C.**

`espcli` is an ongoing project to build a reusable command-line interface for communicating with and debugging ESP32-based embedded systems.

The goal is to interact with a running microcontroller directly from a computer, allowing hardware operations, diagnostics, and testing to be performed through simple terminal commands.

## Motivation

Debugging embedded systems often involves repeatedly modifying firmware, recompiling, and reflashing just to test individual operations.

`espcli` aims to reduce that friction by providing a command interface between the host computer and the microcontroller.

The intended interface would support commands such as:

```bash
gpio write 48 1
gpio read 48
led on
led off
status
uptime
```

These are planned capabilities; hardware integration is not yet implemented.

## Current Progress

The project is currently in its command-parser development stage.

Implemented:
- Command registry using C structures.
- Function-pointer-based command dispatch.
- Interactive command loop.
- Zero-argument command handling.
- Single-argument command handling.
- Basic argument validation.
- Leading and trailing whitespace handling for LED arguments.
- Command success and failure reporting.
- Graceful CLI termination and EOF handling.

## Planned Features

- [ ] Multi-argument command parsing (`argc` / `argv`).
- [ ] Reusable command-processing library.
- [ ] Separate input/output transport from command-processing logic.
- [ ] USB serial communication with ESP32.
- [ ] GPIO read/write operations.
- [ ] LED and peripheral control.
- [ ] System diagnostics (heap, uptime, status).
- [ ] Sensor data querying.
- [ ] Telemetry streaming.
- [ ] Python-based data visualization and monitoring.

## Design Goals

The project is being developed with the following principles:

- **Modularity:** Keep input handling, parsing, command dispatch, and hardware operations separate.
- **Portability:** Keep the command-processing logic independent of ESP-IDF wherever practical.
- **Extensibility:** Make it straightforward to register new commands.
- **Reusability:** Build something that can be carried across future embedded and robotics projects.
- **Testability:** Make the parser testable on a regular Linux system before integrating it with hardware.

## Technology Stack

- Language: C
- Development environment: Linux
- Target hardware: ESP32-S3
- Embedded framework (planned): ESP-IDF
- Host-side interface (planned): Serial terminal / Python tooling

## Project Status

<code>Early development — command parser implementation in progress.</code>

The current implementation is a host-side prototype. Communication with ESP32 hardware and actual peripheral control are future development milestones.

## Long-term Vision

The long-term objective is to develop a lightweight debugging and control interface for embedded systems.

Rather than building a separate debugging tool for every project, `espcli` aims to provide a common interface for interacting with different embedded applications.

**Built incrementally, from the parser up.**
