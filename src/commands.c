#include "../include/commands.h"
#include "../include/gpio_commands.h"
#include <stdio.h>
#include <string.h>

bool help_handler(size_t argc, const char* const argv[]) {
   printf("help_handler called\n");
   // TODO:
   return true;
}

bool status_handler(size_t argc, const char* const argv[]) {
   printf("status_handler called\n");
   // TODO:
   return true;
}

bool uptime_handler(size_t argc, const char* const argv[]) {
   printf("uptime_handler called\n");
   // TODO:
   return true;
}

bool echo_handler(size_t argc, const char* const argv[]) {

   for(size_t i = 0; i < argc; ++ i) {
      printf("%s ", argv[i]);
   }
   printf("\n");
   return true;
}

static const command cmd_regstry[] = {
   [0] = { .keyword = "help", .handler = help_handler },
   [1] = { .keyword = "status", .handler = status_handler },
   [2] = { .keyword  = "uptime", .handler = uptime_handler},
   [3] = { .keyword  = "echo", .handler = echo_handler },
   [4] = { .keyword = "gpio", .handler = gpio_handler},
};

static int find_command(const char *inp_command) {
   if(!inp_command) return -1;

   for(int i = 0; i < (int)sizeof(cmd_regstry)/(int)sizeof(cmd_regstry[0]); ++ i) {
      if(strcmp(inp_command, cmd_regstry[i].keyword) == 0) return i;
   }
   return -1;
}

dispatch_command_status_t dispatch_command(const parsed_command_t *result) {

   if(!result) return DISPATCH_ERROR;
   if(!result->keyword) return DISPATCH_EMPTY_COMMAND;

   if(strcmp(result->keyword, "bye") == 0) return DISPATCH_SUCCESS_EXIT;
   int index_of_command = find_command(result->keyword);
   if(index_of_command < 0) return DISPATCH_COMMAND_NOT_FOUND;
   if(!cmd_regstry[index_of_command].handler) return DISPATCH_ERROR;

   return cmd_regstry[index_of_command].handler(result->argc, result->argv) ? DISPATCH_SUCCESS : DISPATCH_FAILED;
}
