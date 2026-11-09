#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define MAX_COMMAND_SIZE 1000

typedef bool(*interpret_args)(const char*); // declares a universal function signature that returns bool and accepts strings
// turns that signature into a type of its own. Basically sets a blueprint and puts it into a typedef.

typedef struct command{ // the command table element. splits into keyword (first word) that tells what to do
   const char* keyword; // the command
   interpret_args handler; // the command handler. depending on what the command is, the respective function is called,
                           // and the command is "handled"
} command; // the actual command
// basically an array of this structure becomes a table for each command and a command handler defining what it should do


bool help_cmd(const char* cmd) {
   printf("help_cmd called\n");
   // TODO:
   return true;
}

bool status_cmd(const char* cmd) {
   printf("status_cmd called\n");
   // TODO:
   return true;
}

bool led_cmd(const char* cmd) {

   if(!cmd || strlen(cmd) == 0) { printf("led: missing operand\n"); return false; } // no argument provided for a command that requires one
   cmd += strspn(cmd, " \t"); // remove leading whitespace and move the pointer to the start of the useful characters
   if(*cmd == '\0') { printf("led: missing operand\n"); return false; } // only whitespace no argument
   const char *cmd_end = cmd + strlen(cmd) - 1;
   while(cmd_end > cmd && isspace((unsigned char) *cmd_end)) cmd_end --; // remove the trailing whitespace by placing a pointer to the useful


   ptrdiff_t n = cmd_end + 1 - cmd; // number of useful characters

   if(n == 2 && strncmp(cmd, "on", n) == 0) printf("led is ON\n");
   else if(n == 3 && strncmp(cmd, "off", n) == 0) printf("led is OFF\n");
   else { printf("%s: invalid argument for led\n", cmd); return false; }
   return true;
}

bool uptime_cmd(const char* cmd) {
   printf("uptime_cmd called\n");
   // TODO:
   return true;
}

bool echo_cmd(const char* cmd) {

   // TODO: Only prints one word after echo= print the whole string
   if(!cmd) { printf("\n"); return true; }
   printf("%s\n", cmd);
   return true;
}

static const command cmd_regstry[] = {
   [0] = { .keyword = "help", .handler = help_cmd },
   [1] = { .keyword = "status", .handler = status_cmd },
   [2] = { .keyword  = "led", .handler = led_cmd },
   [3] = { .keyword  = "uptime", .handler = uptime_cmd},
   [4] = { .keyword  = "echo", .handler = echo_cmd },
};

int find_command(const char *inp_command) {
   for(int i = 0; i < (int)sizeof(cmd_regstry)/(int)sizeof(cmd_regstry[0]); ++ i) {
      if(strcmp(inp_command, cmd_regstry[i].keyword) == 0) return i;
   }
   return -1;
}

bool command_caller() {
   char inp_command[MAX_COMMAND_SIZE];
   char *keyword = NULL;
   char *arg = NULL;

   printf("\nespcli> ");
   if(!fgets(inp_command, MAX_COMMAND_SIZE, stdin)) {
      if (feof(stdin)) {
              printf("\nEOF received. Exiting...\n");
      }
      else if (ferror(stdin)) {
              printf("\nInput error.\n");
      }
   return false;

   }

   inp_command[strcspn(inp_command, "\n")] = '\0';
   keyword = strtok(inp_command, " \t");
   arg = strtok(NULL, "\n");

   if(!keyword) { printf("Command not entered\n"); return true; }

   if(strcmp(keyword, "exit") == 0) { printf("exiting..\n"); return false; }

   int x = find_command(keyword);
   if(x < 0) { printf("-espcli: %s: command not found\n", keyword); return true; }
   cmd_regstry[x].handler(arg);
   // if(!cmd_regstry[x].handler(arg)) {
   //    printf("command exec failed\n");
   // } else printf("command exec succeeded\n");

   return true;
}

int main(void) {

   bool running = true;

   while(running) {
      running = command_caller();
   }

   return 0;
}
