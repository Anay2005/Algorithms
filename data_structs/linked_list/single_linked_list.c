#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// intializing linked list
typedef struct node
{
    int value;
    struct node *next;
} node;

// intialize head pointer
node *head = NULL;

// function to check if a list is empty
bool isEmpty()
{
    // when head points to NULL linked list is empty
    if (head == NULL)
    {
        return true;
    }
    return false;
}
// search for a number in list
bool search(int k)
{
    node *tra = head;
    // traverse till the end of the list
    while (tra != NULL)
    {
        // match values
        if (tra->value == k)
        {
            return true;
        }
        // if not found move head
        tra = tra->next;
    }
    // if the value is not in the list return false
    return false;
}

// print list starting from head
void print_list()
{
    // create a traversal pointer
    node *tra = head;

    // traverse till the end printing each value
    while (tra != NULL)
    {
        printf("value = %d\n", tra->value);
        tra = tra->next;
    }
    return;
}
// delete a number
void delete(int k, node *p)
{
    // use a pointer to traverse the list
    node *tra = head;

    // if the number is not there in the list return
    if (!search(k))
    {
        return;
    }
    // if head is the one to be removed, free memory accordingly
    if (p == head && p->value == k )
    {
        head = head->next;
        free(p);
        return;
    }
    // if the number is in the list, traverse the list to the position of that number(res)
    while (tra->next->value != k)
    {
        tra = tra->next;
    }
    // connect the previous node relative to current node with the next node relative current node
    p = tra->next;
    tra->next = p->next;
    // free the current node or delete it
    free(p);
    return;
}
// insert between x and the next value pointed to by x
void insert_anywhere(int value, int x)
{
    node *newnode = malloc(sizeof(node));

    if (newnode == NULL)
    {
        return;
    }
    // if list was not created then we cannot insert anywhere
    if (isEmpty())
    {
        return;
    }
    // create a traversal pointer
    node *tra = head;
    // traverse till you find x
    while (tra->value != x)
    {
        tra = tra->next;
    }
    // finally insert newnode carefully without losing the list
    newnode->value = value;
    newnode->next = tra->next;
    tra->next = newnode;
    return;
}
// insert to the front of the linked list(front means where head points)
void insert_to_front(int value)
{
    // request memory to start a linked list
    node *newnode = malloc(sizeof(node));

    // if malloc fails return false
    if (newnode == NULL)
    {
        return;
    }

    // initialize the first value
    if (isEmpty())
    {
        newnode->value = value;
        newnode->next = NULL;

        head = newnode;
        return;
    }

    // insert rest of the values
    newnode->value = value;
    newnode->next = head;
    head = newnode;
    return;
}
void create_list()
{
    insert_to_front(45);
    insert_to_front(4);
    insert_to_front(6);
    insert_to_front(47);
    insert_to_front(90);
    return;
}
// free memory
void free_memory()
{
    // decalre pointers to free memory
    node *p = head;
    node *q = head;
    // free memory without losing the list
    while (q != NULL)
    {
        p = p->next;
        free(q);
        q = p;
    }
    return;
}

// driver function
int main(void)
{
    create_list();
    node *del_head = head;

    insert_anywhere(56, 45);
    // ask for a number to be found
    int number;
    printf("Enter an integer to be found: ");
    scanf("%d", &number);
    // search for a number
    if(search(number))
    {
        printf("Number found\n\n");
    }
    else
    {
        printf("Not found\n\n");
    }
    print_list();
    delete(45, del_head);
    printf("\n");
    print_list();
    free_memory();
    return 0;
}
