/* 
Stack vs. Heap:

Stack:
Memory is managed automatically by the compiler.
Limited in size; typically smaller than the heap.
Faster allocation and deallocation.
Local variables and function call information are stored here.

Heap:
Memory must be managed manually (allocated and freed by the programmer).
Larger in size; limited by the available system memory.
Slower allocation and deallocation.
Used for dynamic memory allocation, like storing data structures or objects.
*/

#include <stdio.h>
#include <stdlib.h>

void stack_example() {
    int localVar = 10;  // Local variable on the stack
    printf("Local Variable: %d\n", localVar);
}

int main() {
    stack_example();
    // localVar is no longer accessible here (out of scope)


    // Allocate memory for an integer on the heap
    int *heapVar = (int*)malloc(sizeof(int));

    if (heapVar != NULL) {
        *heapVar = 20;
        printf("Heap Variable: %d\n", *heapVar);

        // Deallocate the memory when done
        free(heapVar);
    }
    // heapVar is no longer accessible here (memory is freed)

    return 0;
}
