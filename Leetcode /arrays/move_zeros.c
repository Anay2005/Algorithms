#include <stdio.h>
#include <stdlib.h>


void swap(int *a, int *b)
{
    int tmp = *b;
    *b = *a;
    *a = tmp;
    return;
}

void moveZeroes(int* nums, int numsSize) {
    // position_to_insert is the index where the next non-zero number should be inserted
    size_t position_to_insert = 0;
   
    // move the non-zero numbers to the start
    // i is the index of the current number
    for(size_t i = 0; i < numsSize; i++)
    {
        if(nums[i] != 0)
        {
            swap(&nums[position_to_insert], &nums[i]);
            // only increment the position_to_insert after swapping a non-zero number
            position_to_insert++;
        }

        
    }
    return;

    
}
int main() {
    int nums[] = {4, 0, 2, 1, 0, 3, 0};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    moveZeroes(nums, numsSize);

    // Print the array
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }

    return 0;
}