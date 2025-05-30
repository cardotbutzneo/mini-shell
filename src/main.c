#include "main.h"
const char *ALLOWED_COMMANDS[] = {"ls", "cat", "whoami", "date", "pwd", "echo","clear","cd"};


int main(){
    char buffer[100];
    int ret;
    while (1) {
    printf(">>> ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("\n");
        break;
    }

    ret = run_command(buffer);
    if (ret == EXIT_CODE) break; // exit command
    }
    return 0;
}