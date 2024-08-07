#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// length of the array
#define N 5
// implementation of merging function, think of arr[] as the parent array of left and right
void merge(int l[], int nL, int arr[])
{
    // declare iterator, where i is for parent array, j is for left half and k is for right half
    int i = 0, j = 0, k = 0;
    // while both halves are not empty run the loop
    while (j != nL && k != nR)
    {
        // swap if out of order
        if (l[j] < r[k])
        {
            arr[i] = l[j];
            i += 1;
            j += 1;
        }
        else
        {
            arr[i] = r[k];
            i += 1;
            k += 1;
        }
    }
    // at least one of the array is still not empty
    while (j < nL)
    {
        arr[i] = l[j];
        i++;
        j++;
    }

    while (k < nR)
    {
        arr[i] = r[k];
        i++;
        k++;
    }
}
// implementation of sorting function
void mergesort(int a[], int n)
{
    // base case, when array size is less than 2 then the array is sorted
    if (n < 2)
    {
        return;
    }
    // find the middle everytime the function is called
    int smaller_array_size = ceil(n/2) - 1;
    // intialize the temp array
    int temp[smaller_array_size];
    // create temp half every time this function is recursively called
    for (size_t m = 0; m < smaller_array_size; m++)
    {
        temp[m] = a[m];
    }
    int j = 0;
    // shift the right half "smaller array size position" to the left
    for(size_t i = smaller_array_size; i < n; i++)
    {
      
        arr[j] = arr[i];
        j++;
    }

    // sort left half from 0 to mid
    mergesort(temp, smaller_array_size);
    // sort right half from 0 to n-mid
    mergesort(r, n - mid); // split/merge right half
    // merge left and right with their sizes also passed
    merge(l, mid, r, n - mid, a);
}

// implementation of merge sort in c
int main(void)
{
    // declare parent array
    int arr[N];
    srand(time(NULL));
    // generate random input of integers
    for (int i = 0; i < N; i++)
    {
        arr[i] = (rand() % 100);
    }
    // start sorting
    mergesort(arr, N);
    // print sorted array
    for (int j = 0; j < N; j++)
    {
        printf("%i", arr[j]);
        printf(",");
    }
}