#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// intializing linked list
typedef struct node
{
    int value;
    struct node *next;
    struct node *prev;
} node;

node *head = NULL;
node *tmp = NULL;

node* create_sentinel()
{
    node *sent = malloc(sizeof(node));
    return sent;
}
// insert to the front of the linked list
void insert_to_front(int value)
{
    node *newnode = malloc(sizeof(node));
    // if malloc fails return
    if (newnode == NULL)
    {
        return;
    }
    // if head points to Null list is empty
    if (head == NULL)
    {
        // create an empty node with default value of 0
        node *sentinel = create_sentinel();
        // if malloc node creation fails return
        if (sentinel == NULL)
        {
            return;
        }
        // insert the first node carefully
        newnode->value = value;
        sentinel->next = newnode;
        newnode->prev = sentinel;
        head = sentinel;
        tmp = newnode;
        return;
    }
    // insert rest of the values
    newnode->value = value;
    newnode->prev = tmp;
    tmp->next = newnode;
    tmp = newnode;
    return;
}
// function is self explanatory
void make_circular_connection()
{
    node *tra = head->next;
    // traverse till end of the list
    while (tra->next != NULL)
    {
        tra = tra->next;
    }
    // make circular connection
    tra->next = head;
    head->prev = tra;
    return;
}
// function is self explanatory remember to use it after "make_circular_connection"
void break_circular_connection()
{
    // break circular connection
    node *brk = head->prev;
    brk->next = NULL;
    head->prev = NULL;
    return;
}
// create a list
void create_list()
{
    // insert values
    insert_to_front(56);
    insert_to_front(20);
    insert_to_front(5);
    insert_to_front(8);
    return;
}

bool search(int k)
{
    // create a traversal pointer
    node *tra = head;
    // traverse till the end of the list
    while (tra->next != head)
    {
        // match values
        if (tra->value == k)
        {
            return true;
        }
        // if not found move ahead
        tra = tra->next;
    }
    // if last node is the value k
    if(tra->value == k)
    {
        return true;
    }
    // if the value is not in the list return false
    return false;
}

// insert between x and the next value pointed to by x and sentinel node has value 0
void insert_anywhere(int value, int x)
{
    node *newnode = malloc(sizeof(node));

    // if malloc fails exit
    if (newnode == NULL)
    {
        return;
    }
    // if list was not created then we cannot insert anywhere
    if (head == NULL)
    {
        return;
    }
    // if x is not in the list avoid crashing of the program
    if (!search(x))
    {
        return;
    }

    // create a traversal pointer
    node *tra = head;

    // traverse till you find x
    while (tra->value != x)
    {

        // if x is in the last node insert carefully
        if (tra->next == head)
        {
            break_circular_connection();
            newnode->prev = tra;
            tra->next = newnode;
            make_circular_connection();
            return;
        }
        // go to next node
        tra = tra->next;
    }
    // insert node carefully
    newnode->value = value;
    newnode->next = tra->next;
    tra->next = newnode;
    newnode->prev = tra;
    newnode->next->prev = newnode;
    return;
}

void print_list_left_to_right()
{
    // use a traversal pointer
    node *tra = head->next;
    // iterate till the end printing each value
    while (tra->next != head)
    {
        printf("value = %d\n", tra->value);
        tra = tra->next;
    }
    // print the last value
    printf("value = %d\n", tra->value);
    return;
}

// delete a node
void delete(int k)
{
    // use a pointer to traverse the list
    node *tra = head->next;

    // if the number is not there in the list return
    if (!search(k))
    {
        return;
    }

    // traverse till the value is found
    while (tra->value != k)
    {
        tra = tra->next;
    }
    // if last node is the one to be removed, free meomory accordingly
    if (tra->next == head)
    {
        // make connections in correct order
        tra->prev->next = head;
        head->prev = tra->prev;
        // delete the node
        free(tra);
        return;
    }
    // make connections in correct order
    tra->prev->next = tra->next;
    tra->next->prev = tra->prev;
    // delete the node
    free(tra);
    return;
}
// do the same as the print function above but starting from the end
void print_list_right_to_left()
{
    // start from the last node
    node *tra = head->prev;
    // iterate till you reach the start of the list printing value as you traverse
    while (tra->prev != head)
    {
        printf("value = %d\n", tra->value);
        tra = tra->prev;
    }
    // print the first node
    printf("value = %d\n", tra->value);
    return;
}

// free memory
void free_memory()
{
    // decalre pointers to free memory
    node *p = head->next;
    node *q = head->next;
    // free memory without losing the list
    while (q->next != head)
    {
        p = p->next;
        free(q);
        q = p;
    }
    // free the last node
    free(q);
    // free sentinel node
    free(head);
    return;
}
// driver function
int main(void)
{

    create_list();
    make_circular_connection();

    // ask for a number to be found
    int number;
    printf("Enter an integer to be found: ");
    scanf("%d", &number);
    // search for a number
    if (search(number))
    {
        printf("Found\n\n");
    }
    else
    {
        printf("Not found\n\n");
    }
    
    insert_anywhere(4, 20);
    insert_anywhere(7, 8);
    //delete (20);
    print_list_left_to_right();
    printf("\n");
    //print_list_right_to_left();
    free_memory();
    return 0;
}