#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    const char *text = "Operating systems rule\n";
    
    fwrite(text, sizeof(char), strlen(text), stdout);

    // char initials[] = "SA";
    // strcpy(initials, "Sanad");

    // for (int i = 0; i < strlen(initials); ++i) {
    //     printf("%c\n", initials[i]);
    // }


    return 0;
}