#include "main.h"

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
        if (i == (ALLOWED_SIZE-1)){
            printf("  %s ", ALLOWED_COMMANDS[i]);
        }
        printf("  %s, ", ALLOWED_COMMANDS[i]);
    }
    printf("\n");
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
        print_available_commands();
        return 1;
    }

    if (is_allowed_command(args[0]) == 0) {
        printf("Error: command '%s' not allowed\n", args[0]);
        return 1;
    }
    if (!args){
        perror("error NULL pointeur");
        exit(0);
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
        return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    }
}
