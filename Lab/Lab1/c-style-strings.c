#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    const char *text = "Operating systems rule\n";
    
    fwrite(text, sizeof(char), strlen(text), stdout);


    char initials[] = "SA";

    printf("The length of initials before strcpy is: %zu\n", strlen(initials));
    
    strcpy(initials, "Sanad");
    
    printf("The length of initials after strcpy is: %zu\n", strlen(initials));


    return 0;
}