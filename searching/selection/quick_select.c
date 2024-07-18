/*
Implement quick select algorithm to find kth smallest element in an array.
Time complexity: O(n) in average case and O(n^2) in worst case
Space complexity: O(1)
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
// function prototypes
void swap(int *a, int *b);
void print_array(int arr[], int n);
int random_partition(int *arr, int low, int high);
int random_select(int arr[], int low, int high, int k);
void test_random_select(int arr[], int n, int k, int expected);

int main(void)
{
    srand(time(NULL));
    // Test cases
    int arr1[] = {3, 2, 1, 5, 6, 4};
    test_random_select(arr1, 6, 3, 3);

    int arr2[] = {42};
    test_random_select(arr2, 1, 1, 42);

    int arr3[] = {7, 7, 7, 7, 7};
    test_random_select(arr3, 5, 3, 7);

    int arr4[] = {1, 2, 3, 4, 5};
    test_random_select(arr4, 5, 3, 3);

    int arr5[] = {5, 4, 3, 2, 1};
    test_random_select(arr5, 5, 1, 1);

    int arr6[] = {-2, -1, 0, 1, 2};
    test_random_select(arr6, 5, 3, 0);

    int arr7[] = {5, 2, 4, 3, 1};
    test_random_select(arr7, 5, 5, 5);

    int arr8[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    test_random_select(arr8, 9, 1, 1);

    int arr9[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    test_random_select(arr9, 9, 9, 9);

    int arr10[] = {100, 50, 200, 150, 300, 250, 350, 400, 450, 500};
    test_random_select(arr10, 10, 6, 300);

    return 0;
}
void swap(int *a, int *b)
{
    int tmp = *b;
    *b = *a;
    *a = tmp;
    return;
}
int random_select(int arr[], int low, int high, int k)
{
    if(low == high)
    {
        return arr[low];
    }

    int pivot_index = random_partition(arr, low, high);
    // when pivot_index is the kth smallest
    if((pivot_index + 1)  == k)
    {
        return arr[pivot_index];
    }
    // if kth smallest is less than the pivot_index, recurse on the left half
    if(k < (pivot_index + 1))
    {
        return random_select(arr, low, pivot_index - 1, k);
    }
    // This is for the right half
    else
    {
        return random_select(arr, pivot_index + 1, high, k);
    }
}
int random_partition(int *arr, int low, int high)
{
    // get the array size
    size_t arr_size = high - low + 1;
    // generate a random index between 0 and array size
    int random_index = low + (rand() % arr_size);
    swap(&arr[random_index], &arr[low]);
    // set a random pivot
    int pivot = arr[low];
    int i = low + 1;
    int j = high;
    while(i <= j)
    {
        // increment i until an element greater then pivot is not found
        // decrement j until an element less than pivot is not found
        while(i<=j && arr[i] <= pivot)
        {
            i++;
        }
        while(i<=j && arr[j] >= pivot)
        {
            j--;
        }

        if(i < j)
        {
            swap(&arr[i], &arr[j]);
        
        }
    }
    swap(&arr[low], &arr[j]);
    return j;
}
void print_array(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return;
}

void test_random_select(int arr[], int n, int k, int expected) 
{
    int result = random_select(arr, 0, n - 1, k);
    printf("Expected: %d, Result: %d\n", expected, result);
}






