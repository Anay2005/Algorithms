#include <stdio.h>
#include <string.h>

void countSort(int arr[], int n, int max)
{
  // store the count of each digit in an array and input is in range from 0 to max
  int count[max + 1];
  int m;
  int w;
  // intitialize all the indexes in count to 0
  memset(count, 0, sizeof(count));
  // increment count at index arr[j]
  for (int j = 0; j < n; j++)
  {
    count[arr[j]]++;
  }
  // loop to sort the array
  for (int k = 0; k < (max + 1); k++)
  {
    m = 0;
    // stop when m reaches count[k], till then insert at arr[w] the index of count which is
    // k(note index of count corresponds to the elements in the array)
    while (count[k] > 0 && m != count[k])
    {
      arr[w] = k;
      w++;
      m++;
    }
  }
}
// driver function
int main(void)
{
  // intialize array
  int arr[] = {9, 9, 9, 8, 1, 5, 4, 7, 4, 0, 9, 7, 8, 9, 4, 7, 1};
  // get size of array
  int n = sizeof(arr) / sizeof(arr[0]);
  // store the max value of array
  int max = 9;

  // Function call
  countSort(arr, n, max);
  // print sorted array
  for (int i = 0; i < n; i++)
  {
    printf("%d", arr[i]);
  }
  return 0;
}
