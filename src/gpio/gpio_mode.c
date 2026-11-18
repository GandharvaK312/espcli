#include "../../include/gpio_commands.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MODE_COUNT 3

bool gpio_mode(size_t argc, const char *const argv[]) {

   if(argc != MODE_COUNT) { printf("gpio: mode: expected %d arguments\n", MODE_COUNT); return false; }
   if(!argv) { printf("gpio: mode: invalid argument array\n"); return false; }

   long pinNumber;

   parse_gpio_status_t gpio_status = parse_gpio_pin(argv[1], &pinNumber);

   switch(gpio_status) {
      case INPUT_POINTER_ERROR: printf("gpio: mode: invalid input pointer\n"); return false;
      case PIN_IS_NULL: printf("gpio: mode: invalid output pointer\n"); return false;
      case PIN_INVALID: printf("gpio: mode: %s: invalid pin number\n", argv[1]); return false;
      case OVERFLOW_ERROR: printf("overflow/underflow detected\n"); return false;
      case OUT_OF_BOUNDS: printf("gpio: mode: pin number out of valid range\n"); return false;
      case GPIO_PARSE_SUCCESS: break;
   }

   if(strcmp(argv[2], "input") == 0) { printf("setting input mode to pin: %ld\n", pinNumber); }
   else if(strcmp(argv[2], "output") == 0) { printf("setting output mode to pin: %ld\n", pinNumber); }
   else { printf("gpio: mode: %s: invalid mode\n", argv[2]); return false; }

   return true;
}
