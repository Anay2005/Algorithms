/*

Implementation of counting sort algorithm in O(n+k) time best, worst and average case

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_max(int arr[], int size)
{
  // Assume max as the first value
  int max = arr[0];
  for(int i = 0; i<size; i++)
  {
    if(arr[i] > max)
    {
      max = arr[i];
    }
  }
  return max;
}
int find_min(int arr[], int size)
{
  // Assume min as the first value
  int min = arr[0];
  for(int i = 0; i<size; i++)
  {
    if(arr[i] < min)
    {
      min = arr[i];
    }
  }
  return min;
}

void countSort(int arr[], int n, int max, int min)
{
  // Get the range of the unput array
  int range_k = max - min + 1;
  // create a counts array
  int *counts = malloc((range_k)*sizeof(int));
  // Initialize count array with zeros using memset
  memset(counts, 0, range_k * sizeof(int));

  // traverse the input array
  for(int i = 0; i<n; i++)
  {
    // The indexes of counts array corresponds to respective elements in the input array
    // Increment the occurences of elements in input array at relevant indexes in counts array
    counts[arr[i] - min]++;
  }
  // make a cumulative sum of the counts array
  for(int j = 1; j<range_k; j++)
  {
    counts[j] += counts[j-1];
  }
  // modify the original(input) array
  // build the output array
  int *output = malloc(n * sizeof(int));
  for(int i = n-1; i>=0; i--)
  {
    output[counts[arr[i] - min] - 1] = arr[i];
    counts[arr[i] - min]--;

  }
  // copy the output array to the original array
  for(int i = 0; i<n; i++)
  {
    arr[i] = output[i];
  }
  // free the allocated memory
  free(counts);
  free(output);


}

// driver function
int main(void)
{
  // intialize array
  int arr[] = {7,5,5,9,6,6,8};
  // get size of array
  int n = sizeof(arr) / sizeof(arr[0]);
  // store the max and min value of array
  int max = find_max(arr, n);
  int min = find_min(arr, n);


  

  // Function call, a pointer to the first element of arr is passed
  // hence the arr is modified inside the count sort function
  countSort(arr, n, max, min);
  // print sorted array
  for (int i = 0; i < n; i++)
  {
    printf("%d", arr[i]);
  }
  printf("\n");
  return 0;
}
