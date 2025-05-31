#ifndef SHELL_H
#define SHELL_H

#include "main.h"

int is_allowed_command(const char *cmd);
int print_file(const char *filepath);
void print_available_commands();
int exe_cmd(const char args[]);
int run_command(char *input_line);

#endif // SHELL_H