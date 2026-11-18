#include "../../include/gpio_commands.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

typedef enum {
   GPIO_READ,
   GPIO_WRITE,
   GPIO_MODE,
   GPIO_FAILED,
} gpio_operation_t;

gpio_operation_t gpio_operation(const char* const arg) {
   if(!arg) return GPIO_FAILED;
   if( strcmp(arg, "read") == 0) return GPIO_READ;
   if( strcmp(arg, "write") == 0) return GPIO_WRITE;
   if( strcmp(arg, "mode") == 0) return GPIO_MODE;
   return GPIO_FAILED;
}

parse_gpio_status_t parse_gpio_pin(const char *input, long *pin) {

   if(!input) return INPUT_POINTER_ERROR;
   if(!pin) return PIN_IS_NULL;

   char *endptr;

   errno = 0;
   long pinNumber = strtol(input, &endptr, 10);

   if(errno == ERANGE) { return OVERFLOW_ERROR; }

   if(endptr == input || *endptr != '\0') { return PIN_INVALID; }

   if(pinNumber > 48 || pinNumber < 0) { return OUT_OF_BOUNDS; }

   *pin = pinNumber;

   return GPIO_PARSE_SUCCESS;
}

bool gpio_handler(size_t argc, const char* const argv[]) {

   if(argc == 0) { printf("error: No argument entered for gpio\n"); return false; }
   gpio_operation_t arg = gpio_operation(argv[0]);
   switch(arg) {
      case GPIO_READ: return gpio_read(argc, argv);
      case GPIO_WRITE: return gpio_write(argc, argv);
      case GPIO_MODE: return gpio_mode(argc, argv);
      case GPIO_FAILED: printf("-espcli: gpio: %s: invalid argument\n", argv[0]); return false;
   }
   return false;
}
