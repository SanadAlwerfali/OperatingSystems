/* 
Write a program that calls fork().Before calling fork(),have the main process access a variable (e.g., x) 
and set its value to something (e.g., 100). What value is the variable in the child process? 
What happens to the variable when both the child and parent change the value of x?
 */

#include <err.h>
#include <stdio.h>
#include <unistd.h>


int main() {
    int x;

    x = 100;


    pid_t child = fork();
    printf("The child PID is %d\n", child);

    switch (child)
    {
    case -1:
        err(-1, "Error in fork");
    case 0:
        x*=2;
        printf("I am the child, with PID %d Value of x is %d, with this address %p\n", child, x, &x);
        break;
    default:
        printf("I am the parent, Value of x is %d, with this address %p\n", x, &x);
        break;
    }

    return 0;
}