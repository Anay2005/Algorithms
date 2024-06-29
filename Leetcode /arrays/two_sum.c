/*
Implementation of leetcode problem 1, two sum
Given an array of integers, return indices of the two numbers such that they add up to a specific target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// create a node structure
typedef struct Node
{
    struct Node *next;
    int value;
    int key;

} Node;

// create a head pointer structure
typedef struct
{
    Node *head;

} head_pointer;

// now create the hash table structure
typedef struct
{
    head_pointer *table;
    size_t size;

} Hashtable;


// function prototypes

Hashtable* create_hash_table(size_t size);
int Hash_value(int key, int size);
int search(Hashtable *table, int key, int size);
void insert_into_hashtable(Hashtable *table, int key, int value, size_t size);
void free_hash_table(Hashtable* table);



int main(void)
{
    // make an input array
    int nums[] = {3,2,4};
    // get the size of array
    int n = sizeof(nums) / sizeof(nums[0]);
    int target = 6;


    



    // create a hashtable of size n
    Hashtable *table = create_hash_table(n);
    if(table == NULL)
    {
        perror("Failed to create a table\n");
        return 1;
    }
    // make an output array
    int result[] = {0, 0};

    // insert the values from nums into the hashtable
    for(size_t i = 0; i < n; i++)
    {
        insert_into_hashtable(table, nums[i], i, n);
    }
    for(size_t i = 0; i < n; i++)
    {
        // get the key to search for
        int complement = target - nums[i];

        int index = search(table, complement, n);

        if(index != -1 && index != i)
        {
            result[0] = index;
            result[1] = i;
            break;
        }
    }

    // print the result array
    for(size_t i = 0; i < 2; i++)
    {
        printf("%d ", result[i]);
    }
    printf("\n");
    free_hash_table(table);
    return 0;


}
// create a hashtable
Hashtable* create_hash_table(size_t size)
{
    // get memory for the table structure
    Hashtable *table = malloc(sizeof(Hashtable));
    if(table == NULL)
    {
        perror("Memory allocation failed\n");
        return NULL;
    }

    // get memory for the head pointers
    table->table = malloc(size*sizeof(head_pointer));

    if(table->table == NULL)
    {
        perror("Memory allocation failed\n");
        return NULL;
    }

    // initialize the head pointers
    // be very carefule to use .head instead of -> as table->table[i] is a struct
    for(size_t i = 0; i < size; i++)
    {
        table->table[i].head = NULL;
    }

    table->size = size;
    return table;
}

// create a hash function
int Hash_value(int key, int size)
{
    // abs to handle negative keys
    return abs(key) % size;
}

void insert_into_hashtable(Hashtable *table, int key, int value, size_t size)
{
    // get a slot to insert
    int hash_val = Hash_value(key, size);
    // get memory for a newnode to insert
    Node *newnode = malloc(sizeof(newnode));
    if (newnode == NULL)
    {
        perror("Memory allocation failed\n");
        return;
    }
    // Insert the key and value
    newnode->key = key;
    newnode->value = value;
    // insert the first node at the slot
    if(table->table[hash_val].head == NULL)
    {
        table->table[hash_val].head = newnode;
        newnode->next = NULL;
        return;
    }

    // insert the node into nonempty slot at the front
    // make the newnode point to the node where the head points to
    newnode->next = table->table[hash_val].head;
    table->table[hash_val].head = newnode;
    return;





}


// search for an element at a slot
int search(Hashtable *table, int key, int size)
{
    // get the slot
    int hash_val = Hash_value(key, size);

    Node *tra = table->table[hash_val].head;

    while(tra != NULL)
    {
        if(tra->key == key)
        {
            return tra->value;
        }
        tra = tra->next;
    }
    // key not found
    return -1;
}


// Free hash table
void free_hash_table(Hashtable* table)
{
    for (size_t i = 0; i < table->size; i++) 
    {
        Node *current = table->table[i].head;
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table->table);
    free(table);
}
