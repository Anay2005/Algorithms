#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#define QUEUE_EMPTY INT_MIN

//intializing queue data as a linked list
typedef struct node
{
    int value;
    struct node *next;
} node;


//head points to front of queue
node *front = NULL;
//tail points to back of queue
node *rear = NULL;

//function to check if a queue is empty
bool isEmpty()
{
    //when both front and rear point to NULL, the queue is empty
    if(front == NULL && rear == NULL)
    {
        return true;
    }
    return false;

}
//add to a queue and keep track of front and rear
bool enqueue(int value)
{
    //request memory to start a linked list
    node *newnode = malloc(sizeof(node));

    //if malloc fails return false
    if(newnode == NULL)
    {
        return false;
    }
    //initialize the first enqueued value
    if(isEmpty())
    {
        newnode->value = value;
        front = newnode;
        rear = newnode;
        return true;
    }
    //insert rest of the values
    newnode->value = value;
    rear->next = newnode;
    rear = newnode;
    return true;
}
//remember queue adds to end and removes from top hence remove from front
int dequeue()
{

    int result = front->value;
    if(front == rear)
    {
        rear = rear->next;
        return result;
    }
    node *tmp = front;
    front = front->next;
    free(tmp);
    return result;

}

int main(void)
{
    if(isEmpty(front, rear))
    {
       printf("The queue is empty\n");
    }
    enqueue(7);
    enqueue(9);
    enqueue(10);
    if(isEmpty(front, rear))
    {
        printf("The queue is empty\n");
    }
    int t;
    while(rear!=NULL)
    {
        t = dequeue();
        printf("t = %d\n",t);
    }

}