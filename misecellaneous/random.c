#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate different random numbers each time the program is run
void random_generator1() 
{
    // Seed the random number generator 
    // every time the program is run, the same sequence of random numbers will be generated
    // to get different sequence of random numbers, use time(NULL) as seed
    // time(null) or time(0) returns the current time in seconds since the 1st of January 1970
    srand(time(NULL));

    printf("Random generator 1 printing...\n");
    // Generate and print 5 random numbers
    for (int i = 0; i < 5; i++) 
    {
        // generate random number between 0 and RAND_MAX(2147483647)
        int random_number = rand();
        printf("Random number %d: %d\n", i + 1, random_number);
    }
    
}
/*
Use this function to generate the same sequence of random numbers each time 
the program is run.
*/
void random_generator2()
{
    // Try changing the seed value to get different sequence of random numbers
    srand(0);

    printf("Random generator 2 printing...\n");
    for (int i = 0; i < 5; i++) 
    {
        int random_number = rand();
        printf("Random number %d: %d\n", i + 1, random_number);
    }
}
/* 

generate random numbers without seeding the random number generator
Same sequence of random numbers will be generated each time the program 
is run with default seed value of 1

*/

void random_generator3()
{
    printf("Random generator 3 printing...\n");
    for (int i = 0; i < 5; i++) 
    {
        int random_number = rand();
        printf("Random number %d: %d\n", i + 1, random_number);
    }
}

void generate_in_range(int min, int max)
{
    // generate a different number each time the program is run
    srand(time(NULL));
    // Generate random number in the range min to max
    // rand % (max - min + 1) generates a random number between 0 and max - min
    int random_number = (rand() % (max - min + 1)) + min;
    printf("Random number in the range %d to %d: %d\n", min, max, random_number);
}

int main() {
    // Call random_generators
    random_generator1();
    printf("\n");
    random_generator1();
    printf("\n");
    random_generator2();
    printf("\n");
    random_generator2();
    printf("\n");
    random_generator3();
    printf("\n");
    random_generator3();
    printf("\n");

    // Generate random number in the range 10 to 20
    generate_in_range(10, 20);



    // print rand_max
    printf("RAND_MAX: %d\n", RAND_MAX);

    return 0;
}