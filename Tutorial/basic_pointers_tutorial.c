#include <stdio.h>
#include <stdlib.h>

/* 
Reasons why pointers are important

1) Low-Level Memory Access: 
Pointers can store the memory address of other variables, functions, or even other pointers. This allows direct access to memory, which can lead to more efficient programs.
2) Dynamic Memory Allocation: 
Pointers are essential for dynamic memory allocation, such as creating dynamic data structures (like linked lists, trees, and graphs) or allocating memory at runtime.
3) Passing Arguments by Reference: 
When passing variables to a function, C uses pass-by-value, meaning it passes a copy of the variable. However, if you want the function to modify the original variable, you can pass a pointer to the variable.
4) Efficient Memory Management: 
By using pointers, you don’t need to copy large chunks of memory around when passing data to functions.
5) Handling Arrays and Strings: 
Pointers provide a way to use arrays and strings more efficiently. For example, incrementing a pointer is often faster than using array indexing.
*/

void incrementNumValue (int *num) {
    (*num)++;
}

void printArray(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}

int main() {
    int num = 42;


    // Low-Level Memory Access
    // here the *ptr is basically a pointer
    // the &num part is the address of num in the memory
    int *ptr = &num;

    // inside of these print statements we use format specifiers to print valus
    // refer to this for the list of format specifires [https://unstop.com/blog/format-specifiers-in-c] 
    printf("The memory address is: %p\n", &num);
    printf("The value stored inside of that address is: %d\n", *ptr);  

    // now lets try to change the value of num using the pointer
    *ptr = 100; // this will go to that memory address and change the value of it

    printf("The memory address is: %p\n", ptr);
    printf("The new num value is: %d\n", *ptr);


    // Dynamic Memory Allocation
    int *arr = malloc(5 * sizeof(int)); // dynamically allocated array of 5 integers
    if (arr == NULL) {
        printf("Memory allocation failed");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        arr[i] = i;
    }

    for (int i = 0; i < 5; i++) {
        printf("%d", arr[i]);
    }
    free(arr); // free the memory

    // Passing Arguments by Reference
    incrementNumValue(&num);
    printf("\nThe value after we increment %d\n", *ptr);

    // Efficient Memory Management
    //instead of passing the entire array to the function, 
    //we’re just passing the pointer to the array, which is more memory-efficient
    int array[5] = {12, 4, 2, 5, 12};
    printArray(array, 5);
    
    return 0;
}
