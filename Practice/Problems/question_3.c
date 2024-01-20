#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>


int main() {

    int file = open("question_3.txt", O_CREAT | O_RDWR, S_IRWXU);

    char child_greeting[] = "Hello";
    char parent_greeting[] = "Good evening";

    int child = fork();

    switch (child)
    {
    case -1:
        err(-1, "Error buddy");
        break;
    case 0:
        write(file, child_greeting, strlen(child_greeting));
        break;
    default:
        wait(file);
        write(file, parent_greeting, strlen(parent_greeting));
        break;
    }

    return 0;
}