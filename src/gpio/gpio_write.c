#include "../../include/gpio_commands.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define WRITE_COUNT 3

bool gpio_write(size_t argc, const char *const argv[]) {

   if(argc != WRITE_COUNT) { printf("gpio: write: expected %d arguments\n", WRITE_COUNT); return false; }
   if(!argv) { printf("gpio: write: invalid argument array\n"); return false; }

   long pinNumber;

   parse_gpio_status_t gpio_status = parse_gpio_pin(argv[1], &pinNumber);

   switch(gpio_status) {
      case INPUT_POINTER_ERROR: printf("gpio: write: invalid input pointer\n"); return false;
      case PIN_IS_NULL: printf("gpio: write: invalid output pointer\n"); return false;
      case PIN_INVALID: printf("gpio: write: %s: invalid pin number\n", argv[1]); return false;
      case OVERFLOW_ERROR: printf("overflow/underflow detected\n"); return false;
      case OUT_OF_BOUNDS: printf("gpio: write: pin number out of valid range\n"); return false;
      case GPIO_PARSE_SUCCESS: break;
   }

   char *endptr;

   errno = 0;
   long value = strtol(argv[2], &endptr, 10);
   if(endptr == argv[2] || *endptr != '\0') { printf("gpio: write: %s: invalid value\n", argv[2]); return false;}

   if(errno == ERANGE) { printf("overflow/underflow detected\n"); return false; }

   if(value != 0 && value != 1) { printf("gpio: write: %ld: invalid value\n", value); return false; }

   printf("writing to pin: %ld\n", pinNumber);
   printf("value written: %ld\n", value);


   return true;
}
