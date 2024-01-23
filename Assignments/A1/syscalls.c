#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

void help_command() {

    return 0;
}

void read_command(char* path[]) {


    return 0;
}

void write_command(char* path[], char* line_of_text[]) {


    return 0;
}

void mkdir_command(char* path[]) {

    return 0;
}

int main (int argc, char* argv[]) {

    if (argc < 2) {
        printf("missing command");
    };

    const char *command = argv[1];

    if (strcmp(command, "help") == 0) {
        help_command();
    } else if (strcmp(command, "read") == 0){
        read_command(argv[2]);
    } else if (strcmp(command, "write") == 0){
        write_command(argv[2], argv[3]);
    } else if (strcmp(command, "mkdir") == 0){
        mkdir_command(argv[2]);
    } else {
        printf("invalid command");
        return 1;
    }

    return 0;
}