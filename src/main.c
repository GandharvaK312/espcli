#include "../include/commands.h"
#include <stdio.h>

input_status_t read_input(char* buffer, size_t capacity) {
   if(!buffer || capacity == 0) return INPUT_INVALID;

   if(!fgets(buffer, capacity, stdin)) {
      if (feof(stdin)) return INPUT_EOF;
      if (ferror(stdin)) return INPUT_ERROR;
      return INPUT_ERROR;
   }

   buffer[strcspn(buffer, "\n")] = '\0';

   return INPUT_SUCCESS;
}

parse_status_t parse_command(char *buffer, parsed_command_t *result){

   if(!buffer) return PARSE_INVALID_INPUT;
   if(!result) return PARSE_INVALID_OUTPUT;

   *result = (parsed_command_t){0};
   char *keyword = NULL;
   char *argument_token = NULL;

   keyword = strtok(buffer, " \t");
   argument_token = strtok(NULL, " \t\n");

   if(!keyword) return PARSE_EMPTY_INPUT;

   result -> keyword = keyword;
   result -> argc = 0;
   while(argument_token && result -> argc < MAX_ARGS) {
      result -> argv[result -> argc] = argument_token;
      result -> argc ++;
      argument_token = strtok(NULL, " \t\n");
   }

   if(argument_token) return PARSE_TOO_MANY_ARGS;

   return PARSE_SUCCESS;
}

bool process_command() {
   char inp_command[MAX_COMMAND_SIZE];

   printf("\nespcli> ");

   input_status_t inp_status = read_input(inp_command, MAX_COMMAND_SIZE);

   switch(inp_status) {
      case INPUT_INVALID: printf("Invalid input\n"); return false;
      case INPUT_EOF: printf("exiting espcli...\n"); return false;
      case INPUT_ERROR: printf("Input Error\n"); return false;
      case INPUT_SUCCESS: break;
   }

   parsed_command_t result;
   parse_status_t parse_status = parse_command(inp_command, &result);

   switch(parse_status) {
      case PARSE_INVALID_INPUT: printf("invalid input field passed\n"); return false;
      case PARSE_INVALID_OUTPUT: printf("invalid output field passed\n"); return false;
      case PARSE_EMPTY_INPUT: return true;
      case PARSE_TOO_MANY_ARGS: printf("arguments limit exceeded\n"); return true;
      case PARSE_SUCCESS: break;
   }
   // printf("keyword: %s\nargc: %zu\n", result . keyword, result . argc);
   // for(int i = 0; i < result.argc; i ++) {
   //    printf("argv[%d]: %s\n", i, result.argv[i]);
   // }

   dispatch_command_status_t dispatch_status = dispatch_command(&result);
   // printf("dispatch status: %d\n", dispatch_status);

   switch(dispatch_status) {
      case DISPATCH_ERROR: printf("dispatch error. try again\n"); return false;
      case DISPATCH_EMPTY_COMMAND: printf("command not entered \n"); return true;
      case DISPATCH_COMMAND_NOT_FOUND: printf("-espcli: %s: command not found\n", result.keyword); return true;
      case DISPATCH_SUCCESS_EXIT: printf("exiting espcli...\n"); return false;
      case DISPATCH_FAILED: printf("command execution failed\n"); return true;
      case DISPATCH_SUCCESS: break;
   }

   return true;
}

int main(void) {

   bool running = true;

   while(running) {
      running = process_command();
   }

   return 0;
}
