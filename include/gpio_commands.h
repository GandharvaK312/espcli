#ifndef GPIO_COMMANDS_H
#define GPIO_COMMANDS_H

#include <stddef.h>
#include <stdbool.h>

bool gpio_handler(size_t argc, const char* const argv[]);

bool gpio_read(size_t argc, const char * const argv[]);

bool gpio_write(size_t argc, const char * const argv[]);

bool gpio_mode(size_t argc, const char * const argv[]);

#endif
