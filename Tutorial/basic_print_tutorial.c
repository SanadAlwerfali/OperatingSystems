#include <stdio.h>
#include <string.h>

void print_something_for_me(const char *something){
    printf("%s \n",something);
};

int main() {
    char name[] = "Sanad";
    char *name_pointer = &name[0];

    printf("Before changing the value %s \n", name_pointer);

    print_something_for_me(name_pointer); 

    strcpy(name_pointer, "Taha");
    printf("After changing the value %s \n", name_pointer);
    printf("Value of name after changing the value %s \n", name);
    return 0;
}
