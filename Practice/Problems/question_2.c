#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int file = open("question_2.txt", O_CREAT | O_RDWR, S_IRWXU) ;
    char child_name[] = "Sanad Alwerfali\n";
    char parent_name[] = "Alwerfali Sanad\n";

    int child = fork();

    switch (child)
    {
    case -1:
        err(-1, "there is an error buddy");
    case 0:
        write(file, child_name, strlen(child_name));
        break;
    
    default:
        write(file, parent_name, strlen(parent_name));
        break;
    }

    return 0;
}