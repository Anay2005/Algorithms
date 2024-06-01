#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// max length of the array
#define N 5
// function to swap 2 integers
void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}
// implementation of partition function
int partition(int arr[], int start, int end)
{
  // track the left part of the array
  int i = start + 1;
  // choose leftmost element as pivot
  int pivot = arr[start];
  // track the right part of array
  int j = end;
  // iterate till i crosses j, which means we have traversed the array and pivot can be at the centre
  while (i <= j)
  {
    // if arr[i] is less than pivot than it means it is on left half of the centralisez pivot so we move forward
    while (i <= j && arr[i] <= pivot)
    {
      i++;
    }
    // this means the element is on the right half of centralized pivot so we move on
    while (i <= j && arr[j] >= pivot)
    {
      j--;
    }
    // if both while loops stop that means the elements at i and j are in the wrong half so we swap
    if (i < j)
    {
      swap(&arr[i], &arr[j]);
    }
  }
  // make pivot central
  swap(&arr[start], &arr[j]);
  // return pivot_index
  return j;
}

void quicksort(int arr[], int start, int end)
{
  // base condition
  if (start >= end)
  {
    return;
  }

  // rearrange elements across pivot
  int pivot_index = partition(arr, start, end);
  // recur on subarray containing elements that are less than the pivot
  quicksort(arr, start, pivot_index - 1);
  // recur on subarray containing elements that are more than the pivot
  quicksort(arr, pivot_index + 1, end);
}

int main(void)
{
  // intialize array
  int arr[N];
  // seed random generator
  srand(time(NULL));
  // generate random input of integers between 0 and 99
  for (int i = 0; i < N; i++)
  {
    arr[i] = (rand() % 100);
  }
  // quicksort
  quicksort(arr, 0, N - 1);
  // print sorted array
  for (int j = 0; j < N; j++)
  {
    printf("%i", arr[j]);
    printf(",");
  }
}