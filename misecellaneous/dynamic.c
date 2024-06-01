#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    // Allocate memory for 10 integers and remember 'p' points to the memory address of first block(1st integer)
    // remember memory blocks are allocated continugously.
    // for example if [0,10,20,30...90]. And if 0 is at address 400 then 10 is at 404 and 20 at 408...
    // Basically we have an array and we can access its elements using p[i] or *(p+i).
    int *p = malloc(10 * sizeof(int));
    // Memory allocation might fail
    if (p == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    // Initialize the allocated memory with values
    // We can use p[i] as *p[i] is inccorect because p points only to first block hence we cannot dereference other blocks
    // However, p[i] = *(p+i). *(p+i) is dereferencing the pointer at i-th memory block.
    for (int i = 0; i < 10; i++) {
        *(p+i) = i * 10; // Store values in the allocated memory
    }

    // Print the value at the first block
    printf("The value at the first block: %d\n", *p);

    // Example of printing all values to verify
    for (int i = 0; i < 10; i++) {
        printf("Address of p[%d]: %p, Value: %d\n", i, &p[i], *(p+i));
    }

    // Free the allocated memory
    free(p);
}