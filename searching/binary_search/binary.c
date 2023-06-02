#include <stdio.h>

int find_target(int target, int nums[], int N, int start, int end)
{

  int halved_array;
  while (start <= end)
  {
    halved_array = (start + end) / 2;

    if (target == nums[halved_array])
    {
      return halved_array;
    }
    else if (target < nums[halved_array])
    {
      end = halved_array - 1;
    }
    else if (target > nums[halved_array])
    {
      start = halved_array + 1;
    }
  }
  return -2;
}
int main(void)
{

  int nums[] = {2, 3, 5, 7, 8, 10, 12, 15, 18, 20};
  int target;
  int N = sizeof(nums) / sizeof(nums[0]);
  int start = 0;
  int end = N - 1;

  printf("Enter a number to find: ");
  scanf("%d", &target);

  int index = find_target(target, nums, N, start, end);

  if (index == -2)
  {
    printf("Not found\n");
  }
  else
  {
    printf("Found at index: %i\n", index);
  }
}