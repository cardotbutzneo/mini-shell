#include "main.h"
#include "file.h"

void void_buffer_scanf(){
    while(getchar() != '\0');
}

int count_lines(FILE *file) {
    int count = 0;
    int ch;

    rewind(file); // Make sure we start at the beginning
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') count++;
    }
    rewind(file); // Reset again
    return count;
}

int print_file(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        perror("Error: NULL pointer in print_file");
        return -1;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    printf("\n");

    fclose(file);
    return 0;
}