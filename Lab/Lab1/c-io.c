#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fav = 7;
    float floatingPointNumber = 3.14;
    int hexFormattedInteger = 255;
    int *ptr_fav = &fav;

    char myName[] = "Sanad Alwerfali";
    char description[100];

    printf("My favorite integer is %d\n", fav);
    printf("Floating-point number: %f\n", floatingPointNumber);
    printf("Hex-formatted integer: %x\n", hexFormattedInteger);
    printf("Pointer to favorite number: %p\n", ptr_fav);

    sprintf(description, "My name is '%s', which is %zu characters long, and it is located at address %p\n",
    myName, strlen(myName), (void *)myName);

    fwrite(description, sizeof(char), strlen(description), stdout);
    write(STDOUT_FILENO, description, strlen(description));
    return 0;
}