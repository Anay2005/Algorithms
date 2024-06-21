#include <stdio.h>

// function prototypes
void bubble_sort(int arr[], int n);
void print_array(int arr[], int n);
void swap(int *a, int *b);


int main(void)
{
    int arr[] = {5, 4, 8, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    // sort the array
    bubble_sort(arr, n);

    print_array(arr, n);

}

void bubble_sort(int arr[], int n)
{
    // count the no.of swaps made for each pass
    int swap_counter = 0;

    for(int pass = 0; pass < (n - 1); pass++)
    {
        // keep track of current index
        int current_index = 0;
        // reset the swap count after each pass
        swap_counter = 0;
        for(int next_index = 1; next_index < n; next_index++)
        {
            // swap only when the current element is greater than the next
            if(arr[current_index] > arr[next_index])
            {
                swap(&arr[current_index], &arr[next_index]);
                swap_counter++;

            }
            // go to the next pair of elements
            current_index++;


        }
        printf("pass: %d\n", pass);

        // terminate when no swaps are made, which means array is sorted
        if(swap_counter == 0)
        {
            break;
        }
    }
    
}

void print_array(int arr[], int n)
{

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    
}
