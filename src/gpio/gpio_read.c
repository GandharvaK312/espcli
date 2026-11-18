#include "../../include/gpio_commands.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define READ_COUNT 2

bool gpio_read(size_t argc, const char *const argv[]) {

   if(argc != READ_COUNT) { printf("gpio: read: expected %d arguments\n", READ_COUNT); return false; }
   if(!argv) { printf("gpio: read: invalid argument array\n"); return false; }

   long pinNumber;

   parse_gpio_status_t gpio_status = parse_gpio_pin(argv[1], &pinNumber);

   switch(gpio_status) {
      case INPUT_POINTER_ERROR: printf("gpio: read: invalid input pointer\n"); return false;
      case PIN_IS_NULL: printf("gpio: read: invalid output pointer\n"); return false;
      case PIN_INVALID: printf("gpio: read: %s: invalid pin number\n", argv[1]); return false;
      case OVERFLOW_ERROR: printf("overflow/underflow detected\n"); return false;
      case OUT_OF_BOUNDS: printf("gpio: read: pin number out of valid range\n"); return false;
      case GPIO_PARSE_SUCCESS: break;
   }

   printf("reading pin: %ld\n", pinNumber);

   return true;
}
