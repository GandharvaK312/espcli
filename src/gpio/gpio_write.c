#include "../../include/gpio_commands.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define WRITE_COUNT 3

bool gpio_write(size_t argc, const char *const argv[]) {

   if(argc != WRITE_COUNT) { printf("gpio: write: expected %d arguments\n", WRITE_COUNT); return false; }

   char *endptr;

   errno = 0;
   long pinNumber = strtol(argv[1], &endptr, 10);
   if(endptr == argv[1] || *endptr != '\0') { printf("gpio: write: %s: invalid pin number\n", argv[1]); return false;}

   if(errno == ERANGE) { printf("overflow/underflow detected\n"); return false; }

   if(pinNumber > 48 || pinNumber < 0) { printf("pin number out of valid range\n"); return false; }

   printf("writing to pin: %ld\n", pinNumber);

   return true;
}
