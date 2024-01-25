#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

void change_num (int* num) {
    *num = 20;
}
void help_command() {
    char *message = "Usage:  syscalls <command> [arguments]\n";
    write(2, message, strlen(message));
}


int read_command(char* path[]) {
    if (path == NULL || *path == NULL) {
        printf("missing argument\n");
        return 1;
    }

    int file = open(*path, O_RDONLY);

    if (file == -1) {
        printf("Failed to open %s\n", *path);
        return 1;
    }

    char buff[1256];

    int text = read(file, buff, sizeof(buff));

    if (text == -1) {
        printf("Faild to read %s\n", *path);
        return 1;
    }

    buff[text] = '\0';
    write(2, buff, text);
    close(file);
    return 0;
}

int write_command(char* path[], char* line_of_text[], int num_of_lines) {
    if (path == NULL || *path == NULL || line_of_text == NULL || *line_of_text == NULL) {
        printf("missing argument\n");
        return 1;
    }


    int file = open(*path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    
    if (file == -1) {
        printf("Failed to open %s\n", *path);
        return 1;
    }
    
    int total_bytes = 0;
    for (int i = 0; i < num_of_lines; i++) {
        if (line_of_text[i] != NULL) {
            int number_of_bytes = write(file, line_of_text[i], strlen(line_of_text[i]));
            if (number_of_bytes == -1) {
                printf("Failed to write to %s\n", *path);
                return 1;
            }
            total_bytes += number_of_bytes;

            number_of_bytes = write(file, " ", 1);
            if (number_of_bytes == -1) {
                printf("Failed to write to %s\n", *path);
                return 1;
            }
            total_bytes += number_of_bytes;
        }
    }

    printf("Wrote %d B\n", total_bytes);
    close(file);
    return 0;
}

int mkdir_command(char* path[]) {
    mode_t mode = 0700;
    int dir = mkdir(*path, mode);

    if (dir == -1 && errno == EEXIST){
        printf("%s already exists\n", *path);
        return 1;
    } 
    if (dir == -1){
        printf("Faild to create %s\n", *path);
        return 1;
    }

    return 0;
}

int main (int argc, char* argv[]) {
    char* invalid = "invalid command\n";
    char* missing = "missing command\n";

    if (argc < 2) {
        write(2, missing, strlen(missing));
        return 1;
    };

    const char *command = argv[1];

    if (strcmp(command, "help") == 0) {
        help_command();
    } else if (strcmp(command, "read") == 0){
        read_command(&argv[2]);
    } else if (strcmp(command, "write") == 0){ 
        write_command(&argv[2], &argv[3], argc - 3);
    } else if (strcmp(command, "mkdir") == 0){
        mkdir_command(&argv[2]);
    } else {
        write(2, invalid, strlen(invalid));
        return 1;
    }

    return 0;
}