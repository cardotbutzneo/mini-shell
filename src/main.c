#include "main.h"
#include "logs.h"

/*List of allowed commands*/
const char *ALLOWED_COMMANDS[] = {"ls", "cat", "whoami", "date", "pwd", "echo","clear","cd","clogs","version","aboutme","showlogs"};
char LOG_FOLDER_PATH[PATH_MAX];

int main(){
    init_log_folder_path();
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