#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>


#define STACK_EMPTY INT_MIN

typedef struct node
{
    int value;
    struct node *next;
} node;

node* head = NULL; 


bool insert(int value)
{
    //request memory
    node* newnode = malloc(sizeof(node));
    //exit if memory not enough
    if(newnode == NULL)
    {
        return false;
    }
    //The value of newnode is value passed
    newnode->value = value;
    //initialize head pointer
    newnode->next = head;
    //head is a node pointer and points to the entire node
    //If 2 is inserted it would point to node that contains 2
    //If 6 is inserted after head would point to to that 
    head = newnode;
    return true;
}

int withdraw()
{
    //if nothing is inserted then
    if(head == NULL)
    {
        return STACK_EMPTY;
    }
    //remove the frontmost value to which head points
    int result = head->value;
    //create temp so to free the node that has been removed
    //If we free(head) directly then we lose the entire stack
    node* temp = head;
    //make head point to the value that is after the topmost
    head = head->next;

    free(temp);
    return result;
}

int main(void)
{
    insert(56);
    insert(76);
    insert(9);
    insert(10);
    insert(7);
    //arrays looks like [56, 76, 9, 10, 7], 7 is removed first as head points to it

    int t;
    while((t = withdraw()) != STACK_EMPTY)
    {
        printf("t = %d\n",t);
    }
}