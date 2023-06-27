#include <stdio.h>

int recursive_binary_search(int target, int nums[], int N, int start, int end)
{
    if (start > end)
    {
        return -2; // Target not found
    }
    int halved_array = (start + end)/2;
   
    //when found return
    if(target==nums[halved_array])
    {
        return halved_array;
    }
    //conisder left search space
    else if(target<nums[halved_array])
    {
        //set the range
        start = 0;
        end = halved_array-1;
        return recursive_binary_search(target, nums, N, start, end);
    }
    //consider the right search space
    else if(target>nums[halved_array])
    {
        //set the range
        start = halved_array+1;
        end = N-1;
        return recursive_binary_search(target, nums, N, start, end);
    }
    return -2;

    

}

int iterative_binary_search(int target, int nums[], int N, int start, int end)
{
      // loop till the search space is exhausted
    while (start <= end)
    {
        // find the mid-value in the search space and
        // compares it with the target
 
        int mid = (start + end)/2;    // overfstart can happen
        // int mid = start + (end - start)/2;
        // int mid = end - (end - start)/2;
 
        // target value is found
        if (target == nums[mid]) {
            return mid;
        }
 
        // if the target is less than the middle element, discard all elements
        // in the right search space, including the middle element
        else if (target < nums[mid]) {
            end = mid - 1;
        }
 
        // if the target is more than the middle element, discard all elements
        // in the left search space, including the middle element
        else {
            start = mid + 1;
        }
        return -2;
    }
    
}
int main(void)
{

int nums[] = {2, 3, 5, 7, 8, 10, 12, 15, 18, 20};
int target;
int N = sizeof(nums) / sizeof(nums[0]);
int start = 0;
int end = N-1;

printf("Enter a number to find: ");
scanf("%d", &target);

int index = recursive_binary_search(target, nums, N, start, end);

if (index == -2)
{
  printf("Not found\n");
}
else
{
  printf("Found at index: %i\n", index);
}

}