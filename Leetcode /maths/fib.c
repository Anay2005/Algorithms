/* 
Using both recursive approach and iterative to solve this problem.
However, iterative approach is more efficient

Time complexity: O(n) for iterative approach
Space complexity: O(n) for iterative approach

Time complexity: O(2^n) for recursive approach
Space complexity: O(n) for recursive approach
*/

#include <stdio.h>

// function prototypes
int recur_fib(int n);
int iter_fib(int n);



int main(void)
{
    int n;
    printf("Enter an integer n: ");
    scanf("%d\n", &n);

    recur_fib(n);
    iter_fib(n);
}

int recur_fib(int n)
{
    // handle the base cases f(0) and f(1)
    if(n == 0)
    {
        return 0;
    }
    else if(n == 1)
    {
        return 1;
    }
    // use recursion to calculate the (n-1)th and (n-2)th fibonnaci number
    // f_1 is f_(n-1) and f_2 is f_(n-2)
    int f_1 = recur_fib(n-1);
    int f_2 = recur_fib(n-2);
    // add the result to get f(n)
    return f_1 + f_2;
}

int iter_fib(int n)
{
    int F[n + 1];
    F[0] = 0;
    F[1] = 1;

    for(int i = 2; i < n; i++)
    {
        F[i] = F[i - 1] + F[i - 2];
    }
    return F[n + 1];

}