#include "main.h"
const char *ALLOWED_COMMANDS[] = {"ls", "cat", "whoami", "date", "pwd", "echo","clear"};

int main() {
    char buffer[MAX_INPUT];
    int ret;

    while (1) {
        printf(">>> ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\n");
            break;  // EOF or error
        }

        ret = run_command(buffer);
        if (ret == EXIT_CODE) break; // exit command
    }

    printf("Bye!\n");
    return 0;
}
