/*
    * Bucket sort
    * 
    * Bucket sort is a sorting algorithm that works by distributing the elements of an array into a number of buckets. Each bucket is then sorted individually, either using a different sorting algorithm, or by recursively applying the bucket sorting algorithm.
    * 
    * Time complexity:
    *  - Best: O(n+k)
    *  - Average: O(n+k)
    *  - Worst: O(n^2)
    * 
    * Space complexity: O(n+k)
    * 
    * where n is the number of elements in the array and k is the number of buckets.
    * This implementation uses size of buckets = no.of elements
*/

#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
    float value;
    struct node *next;
} node;



// Function prototypes
void bucket_sort_with_floats(float arr[], int n);
void insert_to_front(node **head, float value);
void print_buckets(node **buckets, int n);
void swap(node *a, node *b);
void insertionSort(node **head);
void print_in_sorted_order();


int main(void)
{
    // Make the first input array
    float arr_floats1[] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
    float arr_floats2[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    float arr_floats3[] = {0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1};
    float arr_floats4[] = {0.5, 0.1, 0.5, 0.3, 0.3, 0.7, 0.2, 0.7, 0.1, 0.5};
    float arr_floats5[] = {0.21, 0.23, 0.22, 0.24, 0.25};






    int n_floats1 = sizeof(arr_floats1) / sizeof(arr_floats1[0]);
    // Make the second input array
    int arr_ints[] = {29, 25, 3, 49, 9, 37, 21, 43};

    bucket_sort_with_floats(arr_floats1, n_floats1);
    // bucket_sort_with_floats(arr_floats2, 9);
    // bucket_sort_with_floats(arr_floats3, 9);
    // bucket_sort_with_floats(arr_floats4, 10);
    // bucket_sort_with_floats(arr_floats5, 5);
   


    
}

void bucket_sort_with_floats(float arr[], int n)
{
    // get a pointer to array of pointers
    // All pointers are intialized to NULL
    // These are our buckets
    node **buckets = calloc(n, sizeof(node *));
    if(buckets == NULL)
    {
        perror("Memory allocation. failed");
    }

    // Place the elements
    for(int i = 0; i < n; i++)
    {
        // get the bucket index
        int bucket_index = (int) (n * arr[i]);
        // we pass in the address of node * and the value
        insert_to_front(&buckets[bucket_index], arr[i]);


    }

    // now sort each bucket using insertion sort
    for(int i = 0; i < n; i++)
    {
        // No need to sort if the bucket is empty or has only one element
        if(buckets[i] == NULL || buckets[i]->next == NULL)
        {
            continue;
        }
        insertionSort(&buckets[i]);
    
    }
    printf("\n\n");
    // Print the buckets
    print_buckets(buckets, n);
    printf("\n\n");



}

// insert to the front of the linked list(front means where head points)
// This method to insert happens in O(1)
// node **head holds the address of node *
// Hence the function expects the address of node *
void insert_to_front(node **head, float value)
{
    // request memory to start a linked list
    node *newnode = malloc(sizeof(node));

    // if malloc fails return false
    if (newnode == NULL)
    {
        return;
    }

    // initialize the first value
    if (*head == NULL)
    {
        newnode->value = value;
        newnode->next = NULL;

        *head = newnode;
        return;
    }

    // insert rest of the values
    newnode->value = value;
    newnode->next = *head;
    *head = newnode;
    return;
}


void insertionSort(node **head) 
{
 
  float key;
  // use j to find the position to insert
  node *j;
  // use k to appropriately shift the elements
  node *k;
  // create a pointer to traverse, it points to 2nd element in linked list
  // buckets[i] points to the first element
  node *tra = (*head)->next;
  // iterate till the end of the list
  while (tra != NULL) 
  {
    key = tra->value;
    j = (*head);

    // Move elements of arr[0..i-1], that are greater than key,
    // to one position ahead of their current position
    while (key > j->value && j != tra) {
      j = j->next;
    }
    k = j;
    // make space to insert the value at jth node
    if(j != tra)
    {

        while(k != tra)
        {
            // swap the key and the node at position k
            swap(k, tra);
            k = k->next;
        }
    }
    tra = tra->next;

  }
  print_in_sorted_order(*head);
  
}

void print_buckets(node **buckets, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Bucket %d: ", i);
        node *current = buckets[i];
        while (current != NULL)
        {
            printf("%.2f ", current->value);
            current = current->next;
        }
        printf("\n");
    }
}
void print_in_sorted_order(node *head)
{
    node *tra = head;
    while(tra != NULL)
    {
        printf("%.2f ", tra->value);
        tra = tra->next;
    }
}

// Function to swap two nodes
void swap(node *a, node *b)
{
    float temp = a->value;
    a->value = b->value;
    b->value = temp;
}
