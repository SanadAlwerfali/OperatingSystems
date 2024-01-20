#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

int main() {
    int *one_integer = (int *)malloc(sizeof(int));
    printf("Address of the allocated space is: %p\n", (void *)one_integer);

    int *arr_malloc = (int *)malloc(1000 * sizeof(int));
    int *arr_calloc = (int *)calloc(1000, sizeof(int));


    char *array = (char *)malloc(100 * sizeof(char));
    printf("Address of the allocated space for 100 bytes before de-allocation is: %p\n", (void *)array);

    // set array to NULL
    array = NULL;
    free(array);
    printf("Address of the allocated space for array after setting it to NULL is: %p\n", (void *)array);

    return 0;
}

