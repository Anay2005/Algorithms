// Preprocessor commands to include necessary libraries
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Defining the size of the array
#define N 100

int end;

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

// Function to swap two integer values
void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

// Function to rearrange a heap to maintain the heap property
void heapify(int arr[], int i)
{
  int l = left(i);  // Index of left child
  int r = right(i); // Index of right child
  int largest = i;  // Initialize largest as root

  // If left child is larger than root
  if (l < end && arr[l] > arr[i])
  {
    largest = l;
  }

  // If right child is larger than largest so far
  if (r < end && arr[r] > arr[largest])
  {
    largest = r;
  }

  // If largest is not root
  if (largest != i)
  {
    swap(&arr[largest], &arr[i]); // Swap root and largest
    heapify(arr, largest);        // Recursively heapify the affected sub-tree
  }
}

// Function to create a max heap from an array
void create_heap(int arr[])
{
  int i = (end - 2) / 2; // Start from the last internal node
  while (i >= 0)
  {
    heapify(arr, i--); // Call heapify on all internal nodes
  }
}

// The main function to perform heap sort on an array
void heapsort(int arr[], int n)
{
  end = n;

  // Create a max heap
  create_heap(arr);

  // One by one extract elements from heap
  while (end != 1)
  {
    swap(&arr[0], &arr[end - 1]); // Swap current root with end
    end--;                        // Reduce heap size
    heapify(arr, 0);              // Heapify the new root
  }
}

// The main driver function
int main(void)
{
  // Declare the array
  int arr[N];
  srand(time(NULL)); // Initialize random seed

  // Generate random input of integers
  for (int i = 0; i < N; i++)
  {
    arr[i] = (rand() % 100);
  }

  int n = sizeof(arr) / sizeof(arr[0]); // Get size of array

  // Perform heap sort on the array
  heapsort(arr, n);

  // Print the sorted array
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }

  return 0; // Return statement
}