#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define STACK_EMPTY INT_MIN

typedef struct Graph
{
   int v;
   bool adj_matrix[MAX_VERTICES][MAX_VERTICES]; 
} Graph;


typedef struct node
{
    int value;
    struct node *next;
} node;

node* head = NULL; 


Graph* create_graph(int v)
{
   Graph* g = malloc(sizeof(Graph));
   if(g==NULL)
   {
    printf("graph cannot be created");
    return NULL;
   } 
   g->v = v;
   for (int i = 0; i < v; i++) {
    for (int j = 0; j < v; j++) {
        g->adj_matrix[i][j] = false;
    }
}
    return g;

}

void destroy_graph(Graph* g)
{
   free(g);
}

void Graph_addEdge(Graph* g, int v, int w)
{
    g->adj_matrix[v][w] = true;
}


void Graph_print(Graph* g)
{
    printf("Graph:\n");
    for (int v = 0; v < g->v; v++) {
        for (int w = 0; w < g->v; w++) {
            if (g->adj_matrix[v][w])
            {
                printf("%d -> %d\n", v, w);
            }
        }
    }
}


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

void iterative_DFS(Graph *g, int s, bool visited[])
{
    //insert source node
    insert(s);
    //mark current node as visited
    visited[s] = true;
    //iterate till stack is not empty
    while (head!=NULL)
    {
       //Remove from top of stack or the place where head of linked list points to
       //head pointer points to the next node see withdraw function line 101
       int removed = withdraw();
       //update source node
       s = removed;
       //print the removed node
       printf("%d", removed);
       // get all adjacent nodes of s
       for(int adjacent = 0; adjacent < g->v; adjacent++)
       {
        //if not visited and there is an arrow then insert to stack and mark visited
        if (g->adj_matrix[s][adjacent] && !visited[adjacent]) 
        {
            visited[adjacent] = true;
            //head points to the new node(see line 84) as it is at the top of stack
            insert(adjacent);
        }
       }
        
    }
    

}
void recursive_DFS(Graph *g, int s, bool visited[])
{
    //insert source
    insert(s);
    // Mark the current node as visited
    visited[s] = true;
    // Recur for all the adjacent vertices
    while(head!=NULL)
    {
       //Remove from top of stack or the place where head of linked list points to
       //head pointer points to the next node see withdraw function line 101
       int removed = withdraw();
       //update source node
       s = removed;
       //print the removed node
       printf("%d", removed);
       for (int adjacent = 0; adjacent < g->v; adjacent++)
        {
            if (g->adj_matrix[s][adjacent] && !visited[adjacent])
            {
                recursive_DFS(g, adjacent, visited);
            }
        }

    }

}


//driver function
int main(void)
{
    Graph* g = create_graph(7);
    // Mark all the vertices as not visited
    bool visited[MAX_VERTICES];
    for(int i = 0; i < g->v; i++) 
    {
        visited[i] = false;
    }
    Graph_addEdge(g, 0, 1);
    Graph_addEdge(g, 0, 3);
    Graph_addEdge(g, 0, 6);
    Graph_addEdge(g, 1, 2);
    Graph_addEdge(g, 1, 4);
    Graph_addEdge(g, 4, 5);
    Graph_print(g);
    iterative_DFS(g, 0, visited);
}
 