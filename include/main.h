#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include "sys/stat.h"
#include <dirent.h>
#include <limits.h>

#ifndef MAIN_H
#define MAIN_H

#define MAX_ARGS 20
#define MAX_FILENAME 128
#define MAX_LINES 200 // modify this line if you want to have less log in each logfile
#define ALLOWED_SIZE 13
#define EXIT_CODE 999
#define LOG_PREFIX "log_folder/log_"
#define VERSION "1.0.0"



// List of allowed commands (only names, no args)
extern const char *ALLOWED_COMMANDS[];
extern char LOG_FOLDER_PATH[PATH_MAX];


int is_allowed_command(const char *cmd);
void print_available_commands();
int run_command(char *input_line);
void log_command(const char *command);
void clear_all_logs();

#endif 
