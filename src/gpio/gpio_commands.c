#include "../../include/gpio_commands.h"
#include <stdio.h>
#include <string.h>

typedef enum {
   GPIO_READ,
   GPIO_WRITE,
   GPIO_MODE,
   GPIO_FAILED,
} gpio_operation_t;

gpio_operation_t gpio_operation(const char* const arg) {
   if( strcmp(arg, "read") == 0) return GPIO_READ;
   if( strcmp(arg, "write") == 0) return GPIO_WRITE;
   if( strcmp(arg, "mode") == 0) return GPIO_MODE;
   return GPIO_FAILED;
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
