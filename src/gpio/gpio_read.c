#include "../../include/gpio_commands.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define READ_COUNT 2

bool gpio_read(size_t argc, const char *const argv[]) {

   if(argc != READ_COUNT) { printf("gpio: read: expected %d arguments\n", READ_COUNT); return false; }

   char *endptr;

   errno = 0;
   long pinNumber = strtol(argv[1], &endptr, 10);
   if(endptr == argv[1] || *endptr != '\0') { printf("gpio: read: %s: invalid pin number\n", argv[1]); return false;}

   if(errno == ERANGE) { printf("overflow/underflow detected\n"); return false; }

   if(pinNumber > 48 || pinNumber < 0) { printf("pin number out of valid range\n"); return false; }

   printf("reading pin: %ld\n", pinNumber);

   return true;
}
