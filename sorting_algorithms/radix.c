
/*

Implementation of radix sort in O(d(n+k)) time in all 3 cases where
n is the size of the array and d is the max no.of digits. n+k comes from using
counting sort
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// function prototypes

int find_max(int arr[], int size);
int find_min(int arr[], int size);
void countSort(int arr[], int n, int digit);
int get_max_digit(int arr[], int n);
void radix_sort(int arr[], int n, int max_digits);
void printArray(int arr[], int n);

int main(void)
{
  // input array
  int array[] = {29, 83, 471, 36, 91, 8};
  // get the size of the array
  int n = sizeof(array) / sizeof(array[0]);
  // first generalize getting the max digit(3 in this case for 471) of any array
  int max_digits = get_max_digit(array, n);
  // call the radix sort function
  radix_sort(array, n, max_digits);

  printArray(array, n);
}

int find_max(int arr[], int size)
{
  // Assume max as the first value
  int max = arr[0];
  for (int i = 0; i < size; i++)
  {
    if (arr[i] > max)
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
  for (int i = 0; i < size; i++)
  {
    if (arr[i] < min)
    {
      min = arr[i];
    }
  }
  return min;
}

void countSort(int arr[], int n, int exp)
{

  // make a temp array
  int temp_digit_holder[n];
  // make a output array
  int output[n];

  // traverse the input array to increase the count of each digit
  for (int i = 0; i < n; i++)
  {
    // get the digit at the current position
    int digit = (arr[i] / (int)pow((double)10, (double)exp)) % 10;

    // store the digit in temp array first
    temp_digit_holder[i] = digit;
  }
  printArray(temp_digit_holder, n);
  // find the max and min of temp array
  int max_digit = find_max(temp_digit_holder, n);
  int min_digit = find_min(temp_digit_holder, n);
  // get the range of the temp array
  int range_digit = max_digit - min_digit + 1;
  // now make a counts array intialized with zeros
  int *counts_digit = calloc(range_digit, sizeof(int));
  // traverse the temp array to increase the count of each digit
  for (int i = 0; i < n; i++)
  {
    // The indexes of counts array corresponds to respective elements in the input array
    // Increment the occurences of elements in input array at relevant indexes in counts array
    counts_digit[temp_digit_holder[i] - min_digit]++;
  }

  printf("\n\n");
  // make a cumulative sum of the counts array
  for (int j = 1; j < range_digit; j++)
  {
    counts_digit[j] += counts_digit[j - 1];
  }

  // modify the original(input) array and build the output array
  for (int i = n - 1; i >= 0; i--)
  {
    output[counts_digit[temp_digit_holder[i]] - 1] = arr[i];
    counts_digit[temp_digit_holder[i]]--;
  }
  // copy the output array to the original array
  for (int i = 0; i < n; i++)
  {
    arr[i] = output[i];
  }

  // free the allocated memory
  free(counts_digit);
}
// Use an iterative method to get max no.of_digits of a particular number in array
// same can be achieved with recursion
int get_max_digit(int arr[], int n)
{
  int max_digit = -1;

  for (int i = 0; i < n; i++)
  {
    int quotient = arr[i];
    int count_digits = 0;

    while (quotient != 0)
    {

      // change the quotient for example 3241/10 gives a quotient of 324 discarding 1 to form an int
      // and in the next step 324/10 gives quotient as 32
      quotient /= 10;
      // count the digits extracted
      count_digits++;
    }
    // get the max digit extracted
    if (count_digits > max_digit)
    {
      max_digit = count_digits;
    }
  }
  return max_digit;
}

void radix_sort(int arr[], int n, int max_digits)
{

  for (int exp = 0; exp < max_digits; exp++)
  {
    countSort(arr, n, exp);
  }
}
void printArray(int arr[], int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
}