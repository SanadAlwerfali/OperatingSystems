#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

void help_command() {
    char *message = "Usage:  syscalls <command> [arguments]\n";
    write(2, message, strlen(message));
}

void read_command(char* path[]) {


}

void write_command(char* path[], char* line_of_text[]) {


}

void mkdir_command(char* path[]) {

}

int main (int argc, char* argv[]) {

    if (argc < 2) {
        printf("missing command\n");
        return 1;
    };

    const char *command = argv[1];

    if (strcmp(command, "help") == 0) {
        help_command();
    } else if (strcmp(command, "read") == 0){
        read_command(&argv[2]);
    } else if (strcmp(command, "write") == 0){
        write_command(&argv[2], &argv[3]);
    } else if (strcmp(command, "mkdir") == 0){
        mkdir_command(&argv[2]);
    } else {
        printf("invalid command\n");
        return 1;
    }

    return 0;
}