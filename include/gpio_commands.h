#ifndef GPIO_COMMANDS_H
#define GPIO_COMMANDS_H

#include <stddef.h>
#include <stdbool.h>

typedef enum {
   INPUT_POINTER_ERROR,
   PIN_INVALID,
   OVERFLOW_ERROR,
   OUT_OF_BOUNDS,
   GPIO_PARSE_SUCCESS,
   PIN_IS_NULL,
} parse_gpio_status_t;

bool gpio_handler(size_t argc, const char* const argv[]);

bool gpio_read(size_t argc, const char * const argv[]);

bool gpio_write(size_t argc, const char * const argv[]);

bool gpio_mode(size_t argc, const char * const argv[]);

parse_gpio_status_t parse_gpio_pin(const char *input, long *pin);

#endif
