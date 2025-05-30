#include "main.h"
#include "file.h"

void init_log_folder_path() {
    if (!getcwd(LOG_FOLDER_PATH, sizeof(LOG_FOLDER_PATH))) {
        perror("getcwd failed");
        exit(1);
    }
    strcat(LOG_FOLDER_PATH, "/log_folder");

    // Crée le dossier s'il n'existe pas
    struct stat st = {0};
    if (stat(LOG_FOLDER_PATH, &st) == -1) {
        if (mkdir(LOG_FOLDER_PATH, 0700) != 0) {
            perror("mkdir failed");
            exit(1);
        }
    }
}

int find_last_log_index() {
    DIR *d = opendir(LOG_FOLDER_PATH);
    struct dirent *entry;
    int max_index = -1;

    if (!d) {
        perror("opendir failed");
        return -1;
    }
    
    while ((entry = readdir(d)) != NULL) {
        int idx;
        if (sscanf(entry->d_name, "log_%d.txt", &idx) == 1 && idx > max_index) {
            max_index = idx;
        }
    }

    closedir(d);
    return max_index;   
}

FILE *create_or_get_logfile() {
    int index = find_last_log_index();
    char filename[MAX_FILENAME];
    FILE *file = NULL;

    if (index >= 0) {
        snprintf(filename, sizeof(filename), "%s/log_%d.txt", LOG_FOLDER_PATH, index);
        file = fopen(filename, "a+");

        if (file && count_lines(file) < MAX_LINES) {
            return file;
        }
        fclose(file);
        index++;
    } else {
        index = 0;
    }

    snprintf(filename, sizeof(filename), "%s%d.txt", LOG_PREFIX,index);
    return fopen(filename, "a+");
}

void log_command(const char *command) {
    if (!command){
        perror("NULL pointeur");
        return;
    }
    FILE *file = create_or_get_logfile();
    if (!file) {
        perror("Unable to open log file");
        return;
    }

    time_t now = time(NULL);
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&now));

    if (!fprintf(file, "[%s] %s\n", time_str, command)){
        printf("Error : log have not be print\n");
    }
    fclose(file);
}

void clear_all_logs() {
    DIR *d = opendir(LOG_FOLDER_PATH);
    struct dirent *entry;
    char filepath[MAX_FILENAME + 32]; // Assez grand pour le chemin complet

    if (!d) {
        perror("opendir failed");
        return;
    }

    while ((entry = readdir(d)) != NULL) {
        if (strncmp(entry->d_name, "log_", strlen("log_")) == 0) {
            snprintf(filepath, sizeof(filepath), "log_folder/%s", entry->d_name);
            if (remove(filepath) != 0) {
                perror(filepath);
            }
        }
    }

    closedir(d);
    printf("All log files have been cleared.\n");
}

void display_all_logs() {
    DIR *d = opendir(LOG_FOLDER_PATH);
    struct dirent *entry;

    if (!d) {
        perror("opendir failed");
        return;
    }

    while ((entry = readdir(d)) != NULL) {
        if (strncmp(entry->d_name, "log_", strlen("log_")) == 0) {
            char filepath[MAX_FILENAME + 64];
            snprintf(filepath, sizeof(filepath), "%s/%s", LOG_FOLDER_PATH, entry->d_name);
            FILE *file = fopen(filepath, "r");
            if (!file) {
                perror("fopen failed");
                continue;
            }
            printf("=== %s ===\n", entry->d_name);
            char line[512];
            while (fgets(line, sizeof(line), file)) {
                printf("%s", line);
            }
            fclose(file);
            printf("\n");
        }
    }

    closedir(d);
}