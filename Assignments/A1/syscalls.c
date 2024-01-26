#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>


void help_command() {
    char *message = "Usage:  syscalls <command> [arguments]\n";
    write(STDOUT_FILENO, message, strlen(message));
}


int read_command(char* path[]) {
    if (path[0] == NULL) {
        fprintf(stderr, "missing argument\n");
        return 1;
    }

    int file = open(*path, O_RDONLY);

    if (file == -1) {
        fprintf(stderr, "Failed to open %s\n", *path);
        return 1;
    }

    char buff[1256];

    int text = read(file, buff, sizeof(buff));

    if (text == -1) {
        fprintf(stderr, "Faild to read %s\n", *path);
        close(file);
        return 1;
    }

    buff[text] = '\0';
    write(STDOUT_FILENO, buff, text);
    close(file);
    return 0;
}

int write_command(char* path[], char* line_of_text[], int num_of_lines) {
    if (path == NULL || *path == NULL || line_of_text == NULL || *line_of_text == NULL) {
        fprintf(stderr, "missing argument\n");
        return 1;
    }

    int file = open(*path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    
    if (file == -1) {
        fprintf(stderr, "Failed to open %s\n", *path);
        return 1;
    }
    
    int total_bytes = 0;
    for (int i = 0; i < num_of_lines; i++) {
        if (line_of_text[i] != NULL) {
            int number_of_bytes = write(file, line_of_text[i], strlen(line_of_text[i]));
            if (number_of_bytes == -1) {
                fprintf(stderr, "Failed to write to %s\n", *path);
                return 1;
            }
            total_bytes += number_of_bytes;

            number_of_bytes = write(file, "\n", 1);
            if (number_of_bytes == -1) {
                fprintf(stderr, "Failed to write to %s\n", *path);
                return 1;
            }
            total_bytes += number_of_bytes;
        }
    }

    fprintf(stdout, "Wrote %d B\n", total_bytes);
    close(file);
    return 0;
}

int mkdir_command(char* path[]) {
    mode_t mode = 0700;
    char *token;
    
    token = strtok(*path, "/");
    char *previous = token;
    
    while( token != NULL ) {
        char *current_token;
        printf( " %s\n", token );
        int dir = mkdir(token, mode);
        if (dir == -1 && errno == EEXIST){
            fprintf(stdout, "%s already exists\n", *path);
            return 1;
        } 
        if (dir == -1){
            fprintf(stdout, "Faild to create %s\n", *path);
            return 1;
        }
        token = strtok(NULL, "/");
    }
    
    return 0;
}

int main (int argc, char* argv[]) {
    char* invalid = "invalid command\n";
    char* missing = "missing command\n";

    if (argc < 2) {
        write(STDERR_FILENO, missing, strlen(missing));
        return 1;
    };

    const char *command = argv[1];

    if (strcmp(command, "help") == 0) {
        help_command();
    } else if (strcmp(command, "read") == 0){
        int command_response = read_command(&argv[2]);
        if (command_response == 1) return 1;
    } else if (strcmp(command, "write") == 0) { 
        int write_command_response = write_command(&argv[2], &argv[3], argc - 3);
        if (write_command_response == 1) return 1;
    } else if (strcmp(command, "mkdir") == 0){
        int mkdir_command_response = mkdir_command(&argv[2]);
        if (mkdir_command_response == 1) return 1;
    } else {
        write(STDERR_FILENO, invalid, strlen(invalid));
        return 1;
    }

    return 0;
}