#include <stdio.h>
#include <stdlib.h>

int main() {
    int *number = (int *)malloc(sizeof(int));

    if (number == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Address of the allocated integer: %p\n", (void *)number);

    free(number);

    return 0;
}
