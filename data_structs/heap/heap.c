#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int N = 8;

// Function to return the index of left child of a node in a heap
int left(int i)
{
    return 2 * i + 1;
}

// Function to return the index of right child of a node in a heap
int right(int i)
{
    return 2 * i + 2;
}
// function to return the index of parent of a node in a heap
int parent(int i)
{
    return floor(i / 2 - 1);
}
// Function to swap two integer values
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
    return;
}
// Function to rearrange a heap to maintain the heap property
void max_heapify(int arr[], int i, int arr_size)
{
    int l = left(i);  // Index of left child
    int r = right(i); // Index of right child
    int largest = i;  // Initialize largest as root

    // If left child is larger than root
    if (l < arr_size && arr[l] > arr[i])
    {
        largest = l;
    }

    // If right child is larger than largest so far
    if (r < arr_size && arr[r] > arr[largest])
    {
        largest = r;
    }

    // If largest is not root
    if (largest != i)
    {
        swap(&arr[largest], &arr[i]);        // Swap root and largest
        max_heapify(arr, largest, arr_size); // Recursively heapify the affected sub-tree
    }
    return;
}
// build a heap in O(n) time
void build_heap(int arr[], int n)
{
    // start from the last internal node and remember this formula for internal node
    int i = (n - 2) / 2;

    for (int j = i; j >= 0; j--)
    {
        // call heapify on all internal nodes
        max_heapify(arr, j, n);
    }
    return;
}

// insert a value into the heap
void insert(int value, int *arr)
{
    // with every insert call, size of array increases by 1
    N = N + 1;
    // Reallocate the array to accommodate the new valu with every insert call
    int *new_arr = realloc(arr, N * sizeof(int));
    // if malloc fails, stop the program from crashing
    if (new_arr == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    // Add the new value to the end of the array
    new_arr[N - 1] = value;
    // start at the new value index
    int i = N - 1;
    // move up the heap swapping when neccesary
    while (i > 0 && value > new_arr[parent(i)])
    {
        swap(&new_arr[i], &new_arr[parent(i)]);
        i = parent(i);
    }

    // Use the new array (example: print the elements)
    for (int j = 0; j < N; j++)
    {
        printf("%d ", new_arr[j]);
    }
    printf("\n");

    return;
}
// delete a value from the heap
void delete(int value, int *arr)
{
    // find the index of the value to be deleted
    int i = 0;
    while (i < N && arr[i] != value)
    {
        if (arr[i] == value)
        {
            break;
        }
        // if the value is not found in the array, return
        if (i == N - 1)
        {
            printf("Value not found\n");
            return;
        }
        i++;
    }

    // swap the value to be deleted with the last element
    swap(&arr[i], &arr[N - 1]);
    // with every delete call, size of array decreases by 1
    N = N - 1;
    // Reallocate the array to accommodate the new value with every insert call
    arr = realloc(arr, N * sizeof(int));
    // if realloc fails, stop the program from crashing
    if (arr == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    // call heapify on the new array
    max_heapify(arr, i, N);

    return;
}
// print the heap
void print_heap(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
// The main driver function
int main()
{
    // make an unordered array
    int static_arr[] = {12, 5, 23, 7, 19, 3, 15, 9};

    // make a dyanmaic array and copy the elemnets from static array
    int *dynamic_arr = malloc(N * sizeof(int));
    // if malloc fails, stop the program from crashing
    if (dynamic_arr != NULL)
    {
        memcpy(dynamic_arr, static_arr, N * sizeof(int));
    }
    else
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    // test all your functions
    build_heap(dynamic_arr, N);
    print_heap(dynamic_arr, N);
    insert(4, dynamic_arr);
    print_heap(dynamic_arr, N);
    delete (5, dynamic_arr);
    print_heap(dynamic_arr, N);
    
    // free the memory
    free(dynamic_arr);
    return 0;
}
