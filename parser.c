#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define MAX_COMMAND_SIZE 1000
#define MAX_ARGS 16

typedef bool(*args_handler)(size_t, const char* const argv[]); // declares a universal function signature that returns bool and accepts strings
// turns that signature into a type of its own. Basically sets a blueprint and puts it into a typedef.

typedef struct {
   const char* keyword;
   args_handler handler;
} command;

typedef struct {
    const char *keyword;
    size_t argc;
    const char *argv[MAX_ARGS];
} parsed_command_t;

typedef enum {
   PARSE_SUCCESS,
   PARSE_EMPTY_INPUT,
   PARSE_INVALID_INPUT,
   PARSE_TOO_MANY_ARGS,
   PARSE_INVALID_OUTPUT
} parse_status_t;

typedef enum {
   INPUT_INVALID,
   INPUT_SUCCESS,
   INPUT_EOF,
   INPUT_ERROR
} input_status_t;

typedef enum {
   DISPATCH_EMPTY_COMMAND,
   DISPATCH_COMMAND_NOT_FOUND,
   DISPATCH_SUCCESS_EXIT,
   DISPATCH_SUCCESS,
   DISPATCH_ERROR,
   DISPATCH_FAILED,
} dispatch_command_status_t;

typedef enum {
   GPIO_READ,
   GPIO_WRITE,
   GPIO_MODE,
   GPIO_FAILED,
} gpio_operation_t;

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

gpio_operation_t gpio_mode(const char* const mode) {
   if( strcmp(mode, "read") == 0) return GPIO_READ;
   if( strcmp(mode, "write") == 0) return GPIO_WRITE;
   if( strcmp(mode, "mode") == 0) return GPIO_MODE;
   return GPIO_FAILED;
}

bool gpio_handler(size_t argc, const char* const argv[]) {

   if(argc == 0) { printf("error: No argument entered for gpio\n"); return false; }
   gpio_operation_t mode = gpio_mode(argv[0]);
   switch(mode) {
      case GPIO_READ: printf("reading...\n"); return true;
      case GPIO_WRITE: printf("writing...\n"); return true;
      case GPIO_MODE: printf("checking mode...\n"); return true;
      case GPIO_FAILED: printf("-espcli: gpio: %s: invalid argument\n", argv[0]); return false;
   }
   return false;
}

static const command cmd_regstry[] = {
   [0] = { .keyword = "help", .handler = help_handler },
   [1] = { .keyword = "status", .handler = status_handler },
   [2] = { .keyword  = "uptime", .handler = uptime_handler},
   [3] = { .keyword  = "echo", .handler = echo_handler },
   [4] = { .keyword = "gpio", .handler = gpio_handler},
};

int find_command(const char *inp_command) {
   for(int i = 0; i < (int)sizeof(cmd_regstry)/(int)sizeof(cmd_regstry[0]); ++ i) {
      if(strcmp(inp_command, cmd_regstry[i].keyword) == 0) return i;
   }
   return -1;
}

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

dispatch_command_status_t dispatch_command(const parsed_command_t *result) {

   if(!result) return DISPATCH_ERROR;
   if(!result->keyword) return DISPATCH_EMPTY_COMMAND;

   if(strcmp(result->keyword, "bye") == 0) return DISPATCH_SUCCESS_EXIT;
   int index_of_command = find_command(result->keyword);
   if(index_of_command < 0) return DISPATCH_COMMAND_NOT_FOUND;

   if(!cmd_regstry[index_of_command].handler(result->argc, result->argv)) return DISPATCH_FAILED;
   else return DISPATCH_SUCCESS;

}

bool process_command() {
   char inp_command[MAX_COMMAND_SIZE];

   printf("\nespcli> ");

   input_status_t inp_status = read_input(inp_command, MAX_COMMAND_SIZE);

   switch(inp_status) {
      case INPUT_INVALID: printf("Invalid input\n"); return false;
      case INPUT_EOF: printf("End of File Error\n"); return false;
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
      case DISPATCH_SUCCESS_EXIT: printf("exiting...\n"); return false;
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
