#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define QUEUE_LENGTH 5

int myqueue[QUEUE_LENGTH];
int *front = NULL;
int *back = NULL;
int i = 0;
int j = 1;

// check if array is empty
bool isEmpty()
{
   if (front == NULL && back == NULL)
   {
      return true;
   }
   return false;
}

// insert at the back of array
void enqueue(int value)
{
   // enter the first value only if array is empty
   if (isEmpty())
   {
      myqueue[i] = value;

      // both front and back point at the same address at the start
      front = &myqueue[i];
      back = &myqueue[i];
      i++;
      return;
   }
   // insert the next value
   myqueue[i] = value;
   // make back pointer point to the new value's address
   back = &myqueue[i];
   i++;
   return;

   // condition to check for end of array
   if (i == QUEUE_LENGTH)
   {
      printf("Queue is full");
      return;
   }
}

// remove from the front
int dequeue()
{
   int value = *front;
   front = &myqueue[j];
   j++;

   return value;
}

// driver function
int main(void)
{
   enqueue(56);
   enqueue(1);
   enqueue(5);
   enqueue(7);
   enqueue(10);

   for (int j = 0; j < i; j++)
   {
      printf("%d\n", myqueue[j]);
   }
   int t;
   while (front != back)
   {
      t = dequeue();
      printf("t = %d\n", t);
   }
   t = dequeue();
   printf("t = %d\n", t);
}