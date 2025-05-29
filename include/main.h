#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#ifndef MAIN_H
#define MAIN_H

#define MAX_ARGS 20
#define MAX_INPUT 256
#define ALLOWED_SIZE 7
#define EXIT_CODE 999


// List of allowed commands (only names, no args)
extern const char *ALLOWED_COMMANDS[];
int is_allowed_command(const char *cmd);
void print_available_commands();
int run_command(char *input_line);

#endif // MAIN_H
