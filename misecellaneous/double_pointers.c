#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // a is a pointer to the first element of the array
    int *p = a[0];
    // Equivalent to above statement
    int *q = &a[0][0];

    printf("The value at second block is: %d and the address of second element is: %p\n", *(p + 1), p + 1);
    printf("The value at the second block is: %d and the address of second element is: %p\n", *(q + 1), q + 1);

    printf("The address of value at start of 2nd row is: %p and the value is: %d\n", *(a + 1), *(*(a + 1)));

    // print the matrix using pointers in O(n) time
    for (int *i = a[0]; i <= a[0] + 8; i++)
    {
        printf("%d ", *i);
    }
    printf("\n");

    /*
    Let's do something more fun with double pointers.
    We can create a 2D array using double pointers.
    */

    // We create a pointer to a pointer which points to the first element of the
    // array of pointers(or memory addresses)
    int **a2 = malloc(3 * sizeof(int *));
    // Make pointers point to the first memory address of the rows
    for (int i = 0; i < 3; i++)
    {
        // Each memory address will point to the first memory
        // address of the first element of the rows, a2[i] is a pointer(stores an address)
        a2[i] = malloc(3 * sizeof(int));
    }
    int value = 1;

    // initialize the array, i points to the first memory address of the rows
    // pointer arithmetic is used to access the other row pointers
    for (int **i = a2; i <= a2 + 2; i++)
    {

        // j points to the first memory address of the first element of the row
        // pointer arithmetic is used to access the other elements of the row
        for (int *j = *i; j <= *i + 2; j++)
        {
            *j = value;
            value++;
        }
    }

    // print the array
    for (int **i = a2; i <= a2 + 2; i++)
    {
        for (int *j = *i; j <= *i + 2; j++)
        {
            printf("%d ", *j);
        }
    }
    printf("\n");
}