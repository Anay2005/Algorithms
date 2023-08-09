#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define STACK_LENGTH 5
#define EMPTY (-1)
#define STACK_EMPTY INT_MIN


int mystack[STACK_LENGTH];
int top = EMPTY;

bool insert(int value)
{
    //if stack is full do not push
    if(top >= STACK_LENGTH-1)
    {
        return false;
    }
    top++;
    mystack[top] = value;
    return true;
}

int withdraw()
{
    if(top == EMPTY)
    {
        return STACK_EMPTY;
    }
    //remove from top of stack where top = 4
    int result = mystack[top];

    //once the value is removed from top of the stack
    //top = 3
    top--;
    return result;
}
  
int main(void)
{
    insert(56);
    insert(76);
    insert(9);
    insert(10);
    insert(7);
    //arrays looks like [56, 76, 9, 10, 7], 7 is removed first

    int t;
    while((t = withdraw()) != STACK_EMPTY)
    {
        printf("t = %d\n",t);
    }
}