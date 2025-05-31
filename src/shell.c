#include "main.h"
#include "logs.h"
#include "file.h"


int is_allowed_command(const char *cmd) {
    if (!cmd){
        perror("NULL pointeur");
        exit(0);
    }
    for (int i = 0; i < ALLOWED_SIZE ; i++) {
        if (strcmp(ALLOWED_COMMANDS[i], cmd) == 0) {
            return 1; // command allowed
        }
    }
    return 0; // not allowed
}



void print_available_commands() {
    printf("Available commands:\n");
    for (int i = 0; i < ALLOWED_SIZE; i++) {
        printf("  %s ", ALLOWED_COMMANDS[i]);
    }
    printf("\n");
}

int exe_cmd( char *args[]){
    if (!args || !args[0]){
        fprintf(stderr, "No command to execute.\n");
        return -1;
    }
    // Fork and execute
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return -1;
    }
    if (pid == 0) {
        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);
        log_command(args[0]); // write the last cmd
        return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    }
}

int run_command(char *input_line) {
    char *args[MAX_ARGS];
    int argc = 0;

    // Remove trailing newline if any
    input_line[strcspn(input_line, "\n")] = '\0';

    // Tokenize input line into args
    char *token = strtok(input_line, " ");
    while (token != NULL && argc < MAX_ARGS - 1) {
        args[argc++] = token;
        token = strtok(NULL, " ");
    }
    args[argc] = NULL;

    if (argc == 0) {
        // Empty input
        return 1;
    }
    

    // Built-in exit
    if (strcmp(args[0], "exit") == 0) {
        return EXIT_CODE; // signal to exit shell
    }

    // Built-in help
    if (strcmp(args[0], "help") == 0) {
        char filepath[MAX_FILENAME];
        
        if (argc == 1){
            snprintf(filepath, sizeof(filepath), "cmd_help/help.txt");
            print_file(filepath);
            log_command(args[0]);
        }
        else if (argc > 1) {
            snprintf(filepath, sizeof(filepath), "cmd_help/%s.txt", args[1]);
            print_file(filepath);
            log_command(args[0]);
        }
        return 1;
    }
    if (strcmp(args[0],"clogs") == 0){
        clear_all_logs();
        return 1;
    }
    if (strcmp(args[0],"version") == 0){
        printf("%s\n",VERSION);
        log_command(args[0]); // write the last cmd
        return 1;
    }
    if (strcmp(args[0],"aboutme") == 0){
        print_file("README.md");
        log_command(args[0]); // write the last cmd
        return 1;
    }
    if (strcmp(args[0],"showlogs") == 0){
        display_all_logs();
        log_command(args[0]); // write the last cmd
    }
    if (is_allowed_command(args[0]) == 0) {
        printf("Error: command '%s' not allowed\n", args[0]);
        log_command(args[0]); // write the last cmd
        return 1;
    }
    if (!args){
        perror("error NULL pointeur");
        exit(0);
    }
    // Built-in cd
    if (strcmp(args[0], "cd") == 0) {
        if (argc < 2) {
            fprintf(stderr, "cd: missing operand\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("cd");
            } 
            else {
                // Reconstituer la commande complète pour le log
                char full_cmd[256] = "cd ";
                strncat(full_cmd, args[1], sizeof(full_cmd) - strlen(full_cmd) - 1);
                log_command(full_cmd);
            }
        }
        return 1;
    }

    exe_cmd(args); // run command if it's not an internal command
    
}