/*
Quick select algorithm optimized with worst case time complexity of O(n)
Median of medians technique is used
*/
#include <stdio.h>
#include <stdlib.h>
// function prototypes
void swap(int *a, int *b);
void print_array(int arr[], int low, int high);
int partition(int *arr, int low, int high, int pivot);
int select_smallest(int arr[], int low, int high, int k);
void test_random_select(int arr[], int n, int k, int expected);
void insertionSort(int arr[], int low, int high);


int main(void)
{
    // Test cases
    // int arr1[] = {12,3,5,7,4,19,26,11,2,20,6,8,15};
    // int k = 5;
    // test_random_select(arr1, 6, 3, 3);
    

    // int arr2[] = {42};
    // test_random_select(arr2, 1, 1, 42);

    // int arr3[] = {7, 7, 7, 7, 7};
    // test_random_select(arr3, 5, 3, 7);

    // int arr4[] = {1, 2, 3, 4, 5};
    // test_random_select(arr4, 5, 3, 3);

    // int arr5[] = {5, 4, 3, 2, 1};
    // test_random_select(arr5, 5, 1, 1);

    // int arr6[] = {-2, -1, 0, 1, 2};
    // test_random_select(arr6, 5, 3, 0);

    // int arr7[] = {5, 2, 4, 3, 1};
    // test_random_select(arr7, 5, 5, 5);

    // int arr8[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    // test_random_select(arr8, 9, 1, 1);

    // int arr9[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    // test_random_select(arr9, 9, 9, 9);

    int arr[] = {12, 3, 5, 7, 4, 19, 26, 11, 2, 20, 6, 8, 15, 1, 13, 18, 17, 14, 21, 22, 23, 24, 25, 16, 10};
    test_random_select(arr, 25, 12, 13);
    

    return 0;
}
void swap(int *a, int *b)
{
    int tmp = *b;
    *b = *a;
    *a = tmp;
    return;
}

void insertionSort(int arr[], int low, int high) 
{

  int key, j;
  for (int i = low; i <= high; i++) {
    key = arr[i];
    j = i - 1;

    // Move elements of arr[0..i-1], that are greater than key,
    // to one position ahead of their current position
    while (j >= low && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}
int select_smallest(int arr[], int low, int high, int k)
{
    
    // get the size of the array
    int n = high - low + 1;
    
    // find the kth smallest until the array size is not divisible by 5
    while(n % 5 != 0)
    {
        // find the minimum element in the array
        // move the min element to the beginning of the array(arr[low])
        for(size_t i = low + 1; i <= high; i++)
        {
            if(arr[i] < arr[low])
            {
                swap(&arr[i], &arr[low]);
            
            }
        }
        // if kth smallest is arr[low] then simply return it
        if(k == 1)
        {
            return arr[low];
        }
        // reduce the size of the array by 1 if kth smallest is not found
        low+=1;
        // now kth smallest is one less than the previous kth smallest in the subarray
        k-=1;
        // Update the size of the subarray
        n = high - low + 1; 
    }
    // once the while loop ends and kth smallest is not found
    // the new subarray will be of size n/5
    // g is the number of 5 element groups
    int g = n / 5;
    

    int truncated_low = low;
    int truncated_high = low + 4;
    // now sort each 5 element group using insertion sort
    for(int i = 0; i < g; i++)
    {
        insertionSort(arr, truncated_low, truncated_high);
        // update the new low and new high;
        truncated_low += 5;
        truncated_high = truncated_low + 4;
    }

    // Collect the medians of each group as the 3rd element in the sorted groups
    int medians[g];
    for (int i = 0; i < g; i++)
    {
        medians[i] = arr[low + 5 * i + 2]; // Median is the 3rd element in the sorted group
    }
    // recursively find the median of medians
    int median_of_medians = select_smallest(medians, 0, g - 1, (g + 1)/ 2);
   

    int pivot_index = partition(arr, low, high, median_of_medians);
    // Determine the position of the partition index
    int position = pivot_index - low + 1;
    // when pivot_index is the kth smallest
    if(position  == k)
    {
        return arr[pivot_index];
    }
    // if kth smallest is less than the pivot_index, recurse on the left half
    if(k < position)
    {
        return select_smallest(arr, low, pivot_index - 1, k);
    }
    // This is for the right half
    else
    {
        return select_smallest(arr, pivot_index + 1, high, k - position);
    }

    
    
   
}
int partition(int *arr, int low, int high, int pivot)
{
    
    // find the pivot and move it to be the leftmost element
    for(int i = low; i < high; i++)
    {
        if(arr[i] == pivot)
        {
            swap(&arr[i], &arr[low]);
            break;
        }
    }

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


void test_random_select(int arr[], int n, int k, int expected) 
{
    int result = select_smallest(arr, 0, n - 1, k);
    printf("Expected: %d, Result: %d\n", expected, result);
}


void print_array(int arr[], int low, int high) 
{
  int i;
  for (i = low; i <= high; i++)
    printf("%d ", arr[i]);
  printf("\n");
}



