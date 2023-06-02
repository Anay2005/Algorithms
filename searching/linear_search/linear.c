#include <stdio.h>

int find_target(int target, int nums[], int N)
{
    for (int i = 0; i < N; i++)
    {
        if (nums[i] == target)
        {
            return i;
        }
    }
    return -2;
}

int main(void)
{
    int nums[] = {45, 60, 54, 80};
    int target;
    int N = sizeof(nums) / sizeof(nums[0]);
    printf("Enter a number to find: ");
    scanf("%d", &target);
    int index = find_target(target, nums, N);
    if (index == -2)
    {
        printf("Not found\n");
    }
    else
    {
        printf("Found at index: %i\n", index);
    }
}
