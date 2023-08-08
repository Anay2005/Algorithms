#include <stdio.h>
#include <math.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int fibonnaci_search(int arr[], int target,int  n)
{
    //initialize fibonnaci numbers
    int fib;
    int fib2 = 0;//(n-1)th fibonnaci number
    int fib1 = 1;//(n-2)th fibonnaci number
    fib = fib1 + fib2;//(n)th fibonnaci number

    /* fibM is going to store the smallest Fibonacci
       Number greater than or equal to n */
    while(fib<n)
    {
        fib2 = fib1;
        fib1 = fib;
        fib = fib1 + fib2;
    }
    // Marks the eliminated range from front
    int offset = -1;
    while(fib>1)
    {
        //we need to insure the min i always is less than length of array
        //offset is used because array is from (0, n-1)
        int index = min(offset + fib2, n-1);

        /* If x is greater than the value at index fib2,
           cut the subarray array from offset to i */
        if (arr[index] < target) 
        {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            //offset is updated to the lowest index in right search space
            offset = index;
        }
 
        /* If x is greater than the value at index fib2,
           cut the subarray after i+1  */
        else if (arr[index] > target) 
        {
            //if both left and right search space has been eliminated once then the middle remians hence offset is not 
            //updated
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        }
 
        /* element found. return index */
        else
            return index;
    }
 
    /* comparing the last element with target */
    if (fib1 && (arr[offset + 1] == target))
        return offset + 1;
 
    /*element not found. return -1 */
    return -1;
}



/* driver function */
int main(void)
{
  int arr[] = { 10, 22, 35, 40, 45, 50, 80, 82, 85, 90, 100, 235};
  int n = sizeof(arr) / sizeof(arr[0]);
  int target = 235;
  int index = fibonnaci_search(arr, target, n);
  if(index>=0)
    printf("Found at index: %d\n",index);
  else
    printf("%d isn't present in the array",target);
    return 0;
}