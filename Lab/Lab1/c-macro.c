#include <stdio.h>
#include <stddef.h>

#define FOO "this is the definition of foo"

void useFoo() {
    char character = FOO[5];
}

int main() {
    printf("%s\n", FOO);
    return 0;
}