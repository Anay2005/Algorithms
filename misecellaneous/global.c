#include <stdio.h>

void increment();
void display();

int main() {
    increment();
    display();
    increment();
    display();
    return 0;
}

void increment() {
    // This is a global variable
    extern int counter; 
    counter++;
}

void display() {
    // This is a global variable
    //extern int counter;  
    printf("Counter: %d\n", counter);
}
// This global variable is allocated memory at compile time
// hence the compiler knows the value of the variable before increment and display functions are called
int counter = 0; 