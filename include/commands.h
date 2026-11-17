#ifndef COMMANDS_H
#define COMMANDS_H

#include "gpio_commands.h"
#include <stdbool.h>
#include <stddef.h>
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
   INPUT_INVALID,
   INPUT_SUCCESS,
   INPUT_EOF,
   INPUT_ERROR
} input_status_t;

typedef enum {
   PARSE_SUCCESS,
   PARSE_EMPTY_INPUT,
   PARSE_INVALID_INPUT,
   PARSE_TOO_MANY_ARGS,
   PARSE_INVALID_OUTPUT
} parse_status_t;

typedef enum {
   DISPATCH_EMPTY_COMMAND,
   DISPATCH_COMMAND_NOT_FOUND,
   DISPATCH_SUCCESS_EXIT,
   DISPATCH_SUCCESS,
   DISPATCH_ERROR,
   DISPATCH_FAILED,
} dispatch_command_status_t;

bool help_handler(size_t argc, const char* const argv[]);

bool status_handler(size_t argc, const char* const argv[]);

bool uptime_handler(size_t argc, const char* const argv[]);

bool echo_handler(size_t argc, const char* const argv[]);

bool execute_command(const parsed_command_t *command);

input_status_t read_input(char* buffer, size_t capacity);

parse_status_t parse_command(char *buffer, parsed_command_t *result);

dispatch_command_status_t dispatch_command(const parsed_command_t *result);

bool process_command();

#endif
