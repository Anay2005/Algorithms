/*
The program will read names of people from the user and store them in an array of strings. 
The program will then print the names.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    // 6 pointers to strings(6 is the max no.of pointers )
    // names[0], names[1]... are pointers
    char *names[6];
    // store each name here by allocating space for 100 chars
    // n is a pointer to the first char and pointer arithmetic is valid 
    char n[100];


    printf("\nEnter the name of the person: ");
    printf("\n");
    for(int i = 0; i < 2; i++)
    {
        // store up to 99 chars reserving space for null terminator
        scanf("%99s", n);
        
        // get the length of the spring
        int len = strlen(n);
        // allocate memory for null terminator
        names[i] = malloc(len + 1);
        // strcpy only works if src and destination are allocated memory
        // Hence line 29 is important
        strcpy(names[i], n);
    }
    printf("\n\n");
    // print the string
    for(int i = 0; i < 2; i++)
    {
        printf("%s\n", names[i]);
    }
    return 0;


}