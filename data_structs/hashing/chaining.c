#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

/*
define the node structure, typedef creates an alias of the structure,
now we can drop struct keyword for further declarations of the node
we must use node at start if we are to use node within the struct as the compiler must know the definition beforehand.

*/

typedef struct Node
{
    /*
    In the definition of struct Node,
    the typedef alias Node is not available until after the closing brace of the structure definition
    */

    struct Node *next;
    struct Node *prev;
    // key asscociated with the node
    int value;
    // Data contained in the node
    int key;

} Node;

// define the head pointers for each slot
typedef struct
{
    Node *head;

} head_pointer;

// Define the HashTable structure
typedef struct
{
    // pointer to the array of elements
    head_pointer *table;
    // Current number of elements in the hash table and the maximum possible size
    int size;

} Hashtable;

// function prototypes
Hashtable *create_hash_table(int size);
int Hash_value(int key, int size);
Node *insert(Hashtable *arr, int value, int key);
void delete_node(Hashtable *arr, Node *node);
void print_table(Hashtable *arr, int size_of_table);
Node* search(Hashtable *arr, int key);

int main(void)
{
    // create a hash table
    Hashtable *table = create_hash_table(SIZE);
    int values[] = {10, 20, 34, 56, 64, 13};
    int keys[] = {5, 30, 92, 83, 54, 12};
    int length_of_data = sizeof(values) / sizeof(values[0]);
    Node *nodes[length_of_data];

    // insert values into the hash table
    for (int i = 0; i < length_of_data; i++)
    {
        nodes[i] = insert(table, values[i], keys[i]);
    }
    printf("%d\n", nodes[1]->value);

    // print the table after inserting
    print_table(table, SIZE);

    printf("\n\n");
    // delete the node
    delete_node(table, nodes[1]);
    // search for a key
    Node *node = search(table, 106);
    if(node != NULL)
    {
        printf("The node is: %d %d\n", node->key, node->value);

    }
    else
    {
        printf("Node not found\n\n");
    }


    // print table after deleting
    print_table(table, SIZE);

    return 0;
}

Hashtable *create_hash_table(int size)
{
    // Allocate memory for the HashTable
    Hashtable *array = malloc(sizeof(Hashtable));
    // if malloc fails, return NULL
    if (array == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    // Allocate memory for head pointers of each slot in the hash table.
    array->table = malloc(size * sizeof(head_pointer));
    if (array->table == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    // initialize the head pointers
    for (int i = 0; i < size; i++)
    {
        array->table[i].head = NULL;
    }
    // Set the current size to size
    array->size = size;
    // Return the newly created HashTable
    return array;
}
// create a hash function
int Hash_value(int key, int size)
{
    return key % size;
}

// insert at the front of the chain
Node *insert(Hashtable *arr, int value, int key)
{
    // get a slot in the table or hash value
    int hash_val = Hash_value(key, arr->size);
    // get memory for a newnode
    Node *newnode = malloc(sizeof(Node));
    if (newnode == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    // Insert the first node at a relevant slot given by the hash value if that slot is empty
    if (arr->table[hash_val].head == NULL)
    {
        // set data, use strictly arrow notation because newnode is a pointer
        newnode->value = value;
        newnode->key = key;
        // initialize the pointers
        newnode->prev = NULL;
        newnode->next = NULL;


        /*
        make the head pointer for that slot point to this first node. Use strictly '.'
        notation as 'table' points to an array of head pointers but table[hash_val] is not a pointer but
        a structure(head_pointer) at index hash_val.
        */
        arr->table[hash_val].head = newnode;
        return newnode;
    }
    // insert nodes which are not the first one at non-empty slots
    newnode->value = value;
    newnode->key = key;
    // initialize the pointers
    newnode->prev = NULL;
    newnode->next = NULL;

    // carefully make a doubly linked list
    newnode->next = arr->table[hash_val].head;
    // head is a node pointer hence we use arrow notation again.
    arr->table[hash_val].head->prev = newnode;
    arr->table[hash_val].head = newnode;
    return newnode;
}

void delete_node(Hashtable *arr, Node *node)
{
    int hash_val = Hash_value(node->key, SIZE);

    // if there is only a single element in the slot
    if(node->next == NULL && node->prev == NULL)
    {
        arr->table[hash_val].head = NULL;
        free(node);
        return;
    }
    // if the node to be deleted is first
    if (node->prev == NULL)
    {
        arr->table[hash_val].head = node->next;
        free(node);
        node = arr->table[hash_val].head;
        node->prev = NULL;

        return;
    }
    // if the node is last
    if (node->next == NULL)
    {
        node->prev->next = NULL;
        free(node);
        return;
    }
    // else the node is in the middle
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
    return;
}

void print_table(Hashtable *arr, int size_of_table)
{

    // print the hashtable
    for (int j = 0; j < size_of_table; j++)
    {

        Node *tmp = arr->table[j].head;
        if (arr->table[j].head != NULL)
        {

            // print the value and key
            while (tmp != NULL)
            {

                printf("%d %d\n", tmp->value, tmp->key);
                // move to the next node
                tmp = tmp->next;
            }
        }
    }
}

Node* search(Hashtable *arr, int key)
{
    int hash_val = Hash_value(key, SIZE);
    Node *srch = arr->table[hash_val].head;

    while (srch != NULL)
    {
       if(srch->key == key)
       {
        printf("Node found\n");
        return srch;
       }
       srch = srch->next;
    
    }
    return NULL;

    
}