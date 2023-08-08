#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5

// Function to perform insertion sort on `arr[]`
void InsertionSortItearative(int arr[], int n)
{
    // start from the second element (the element at index 0
    // is already sorted)
    for (int i = 1; i < n; i++)
    {
        int value = arr[i];
        int j = i;

        // find index `j` within the sorted subset `arr[0…i-1]`
        // where element `arr[i]` belongs
        while (j > 0 && arr[j - 1] > value)
        {
            arr[j] = arr[j - 1];
            j--;
        }

        // note that the subarray `arr[j…i-1]` is shifted to
        // the right by one position, i.e., `arr[j+1…i]`

        arr[j] = value;
    }
}
void InsertionSortRecursive(int arr[], int n)
{
    if (n <= 1)
    {
        return;
    }
    InsertionSortRecursive(arr, n - 1);
    InsertionSortItearative(arr, n);
}

int main(void)
{
    // intialize array
    int arr[N];
    // seed random generator
    srand(time(NULL));
    // generate random input of integers
    for (int i = 0; i < N; i++)
    {
        arr[i] = (rand() % 100);
    }
    InsertionSortRecursive(arr, N);

    // print sorted array
    for (int j = 0; j < N; j++)
    {
        printf("%i", arr[j]);
        printf(",");
    }
    printf("\n");
}
