#include <stdio.h>
#include <stdlib.h>
// define the no.of buckets in the hash table
#define SIZE 10


typedef struct Node
{
    int value;
    int key;
    struct Node *next;
} Node;




typedef struct Hashtable
{
    // points to a pointer to all the head pointers
    Node **head_pointer;
    size_t size;
} Hashtable;


// function prototypes
Hashtable* create_hash_table(size_t size);
int hash(int key, size_t size);
void insert(Hashtable *table, int key, int value, size_t size);
void print_table(Hashtable *table, size_t size);
void free_hashtable(Hashtable *table, size_t size);





int main(void)
{
    // create a hashtable of SIZE
    Hashtable *table = create_hash_table(SIZE);
    // check for memory allocation failure
    if (table == NULL) 
    {
        return 1;  
    }
    // these two variables are allocated memory on the stack
    // hence we can use scanf to store the user inputted value here
    int key;
    int value;
    // insert 3 nodes
    for(int i = 0; i < 3; i++)
    {
        printf("Enter the key: ");
        scanf("%d", &key);

        printf("\n");

        printf("Enter the value: ");
        scanf("%d", &value);

        printf("\n\n");

        insert(table, key, value, SIZE);

    }
    print_table(table, SIZE);
    free_hashtable(table, SIZE);
    return 0;

}

// make a hash function
int hash(int key, size_t size)
{
    return key % size;
}

Hashtable* create_hash_table(size_t size)
{
    // Ask memory to store the struct
    Hashtable *table = malloc(sizeof(Hashtable));
    if(table == NULL)
    {
        perror("Memory allocation failed");
        return NULL;
    }
    // Ask memory for node type head pointers
    // table->head_pointer is a pointer to the memory location of the first (Node *)
    table->head_pointer = malloc(size*sizeof(Node*));
    if(table->head_pointer == NULL)
    {
        perror("Memory allocation failed");
        free(table);
        return NULL;
    }
    // initialize the head pointers to NULL
    for(size_t i = 0; i < size; i++)
    {
        table->head_pointer[i] = NULL;
    }
    // set the size
    table->size = size;
    return table;


}

void insert(Hashtable *table, int key, int value, size_t size)
{
    int hash_val = hash(key, size);

    Node *newnode = malloc(sizeof(Node));

    newnode->key = key;
    newnode->value = value;
    // insert the first node
    if(table->head_pointer[hash_val] == NULL)
    {
        table->head_pointer[hash_val] = newnode;
        newnode->next = NULL;
        return;
    }

    // inserting at the front is faster
    newnode->next = table->head_pointer[hash_val];
    table->head_pointer[hash_val] = newnode;
    return;
}

void print_table(Hashtable *table, size_t size)
{
    for(size_t i = 0; i < size; i++)
    {
        // use this to traverse each bucket
        Node *tra = table->head_pointer[i];
        printf("Bucket %zu: ", i);

        while(tra != NULL)
        {
            printf("%d ", tra->value);
            tra = tra->next;
        }
        printf("\n");
    }
    return;
}

void free_hashtable(Hashtable *table, size_t size)
{
    for(int i = 0; i < size; i++)
    {
        Node *current = table->head_pointer[i];
        // carefully free the memory for all the nodes
        while(current != NULL)
        {
            Node *tmp = current;
            current = current->next;
            free(tmp);
        }
    }

    // free all the head pointers
    free(table->head_pointer);
    // free the hashtable structure
    free(table);
   

}