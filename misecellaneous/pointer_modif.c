#include <stdio.h>
#include <stdlib.h>
// Function that takes a single pointer and expects an address as input
void modifySinglePointer(int *ptr) {
    int y = 20;
    // This only changes the local copy of ptr(address) passed as argument from main. Nothing is changed outside this function
    ptr = &y; // 
}


void modify_double_pointer(int **dptr)
{
    // This variable is destroyed when function ends
    int y = 20;
    // *dptr is a pointer to the integer x(10) which holds the address of x and **dptr gives the value(10 which is being changed)
    // dptr holds the address of ptr(the argument of the function) beause we passed in the address of ptr
    //  we change the address of x to hold the addres of 'y' *ptr now points to y(address of 
    *dptr = &y;
    // memory location of y is no longer valid outside the function hence this function won't correctly work
}

void correct_modification(int **dptr)
{
    // dynamically allocated memory is valid outside the function however pointer variable 'y' is local to this function.
    int *y = malloc(sizeof(int));
    // remember dereferencing a single pointer gives the value
    *y = 20;
    // be careful now y is a pointer(holds the address of 20) and we do not need &y as *dptr must point to the address y points to(20)
    // and not the address of y itself.
    // The memory location requested  is now also pointed to by *dptr(aka ptr) 
    *dptr = y;

}

int main(void)
{
    int x = 10;
    // ptr is a variable that is being assigned the address(&) of x. ptr can be dereferenced using *ptr to get the value of x
    // remember 'ptr' has a memory address that could be obtained using &ptr
    int *ptr = &x;
    printf("The dereferenced value of ptr before is: %d\n", *ptr);
    printf("The address of x before is: %p\n", ptr);
    printf("The address of ptr is: %p\n", &ptr);

    // we are passing in the address of x, only a copy of that address is passed 
    modifySinglePointer(ptr);
    printf("\n\n");

    printf("The dereferenced value of ptr  after is: %d\n", *ptr);
    printf("The address of x after is: %p\n", ptr);
    // we need to pass the address of 'ptr'
    modify_double_pointer(&ptr);
    printf("\n\n");

    // garbage value is printed
    printf("The dereferenced value of ptr after is: %d\n", *ptr);
    printf("The address of x after is: %p\n", ptr);

    printf("\n\n");

    correct_modification(&ptr);

    printf("The dereferenced value of ptr after is: %d\n", *ptr);
    printf("The address of x after is: %p\n", ptr);







}