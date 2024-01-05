/* impelmentation of direct addresing */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

// Define the Node structure
typedef struct
{
    // key asscociated with the node
    int key;
    // Data contained in the node
    int data;
} Node;

// Define the HashTable structure
typedef struct
{
    // Pointer to the array of elements
    Node *table;
    // Current number of elements in the hash table and the maximum possible size
    int size;
} HashTable;

// Function prototypes
HashTable* create_hash_table(int size);
void direct_address_insert(HashTable *hashTable, int value, int key);
Node direct_address_search(HashTable *hashTable, int key);
void direct_address_delete(HashTable *hashTable, int key);
void print_hash_table(HashTable *hashTable);
void free_hash_table(HashTable *hashTable);

// driver code
int main(void)
{
    HashTable *table = create_hash_table(SIZE);
    // insert values into the hash table
    direct_address_insert(table, 5, 6);
    direct_address_insert(table, 6, 7);
    direct_address_insert(table, 7, 8);
    direct_address_insert(table, 8, 9);
    // print the hash table
    print_hash_table(table);
    printf("\n");
    // search for a value in the hash table
    Node node = direct_address_search(table, 20);
    // delete a value from the hash table
    direct_address_delete(table, 6);
    // print the hash table
    print_hash_table(table);
    printf("\n");
    // print the key and data
    printf("%d %d\n", node.data, node.key);

    return 0;
}
// create a new hash table
HashTable *create_hash_table(int size)
{
    // Allocate memory for the HashTable
    HashTable* array = malloc(sizeof(HashTable));
    // if malloc fails, return NULL
    if (array == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    // Allocate memory for the array of elements or nodes
    array->table = malloc(size * sizeof(Node));
    // if malloc fails, return NULL
    if (array->table == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    // Set the current size to size
    array->size = size;
    // Return the newly created HashTable
    return array;
}
// insert a value into the hash table
void direct_address_insert(HashTable *arr, int value, int key)
{
    // check if the key is in range
    if (key >= arr->size)
    {
        printf("Key out of range\n");
        return;
    }
    // make a new node
    Node new_node;
    // set the key and data
    new_node.key = key;
    new_node.data = value;
    // insert the node into the hash table
    arr->table[key] = new_node;
    return;
}
// direct address search
Node direct_address_search(HashTable *arr, int key)
{
    // check if the key is in range
    if (key >= arr->size)
    {
        printf("Key out of range\n");
        // Create an empty Node
        Node emptyNode;
        // Set the priority to -1
        emptyNode.key = -1;
        // Set the data to -1
        emptyNode.data = -1;
        // Return the empty Node
        return emptyNode;
    }
    // return the node at the key
    return arr->table[key];
}
// direct address delete
void direct_address_delete(HashTable *arr, int key)
{
    // check if the key is in range
    if (key >= arr->size)
    {
        printf("Key out of range\n");
        return;
    }
    // delete the node at the key
    arr->table[key].key = 0;
    arr->table[key].data = 0;
    return;
}
// print the hash table
void print_hash_table(HashTable *table)
{
    // iterate through the hash table
    for (int i = 0; i < table->size; i++)
    {
        // print the key and data
        printf("%d %d\n", table->table[i].data, table->table[i].key);
    }
    return;
}
// free the hash table
void free_hash_table(HashTable *table)
{
    // free the array of nodes
    free(table->table);
    // free the hash table
    free(table);
    return;
}

