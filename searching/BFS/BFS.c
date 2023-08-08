#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_VERTICES 50
typedef struct Graph
{
   int v;
   bool adj_matrix[MAX_VERTICES][MAX_VERTICES]; 
} Graph;

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

// Prints BFS traversal from a given source s
void Graph_BFS(Graph* g, int s)
{
    // Mark all the vertices as not visited
    bool visited[MAX_VERTICES];
    for (int i = 0; i < g->v; i++) {
        visited[i] = false;
    }
 
    // Create a queue for BFS
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;
 
    // Mark the current node as visited and enqueue it
    visited[s] = true;
    // At this point rear = front
    queue[rear] = s;
    rear++;
 
    while (front != rear) {
        // Dequeue a vertex from front of queue and print it
        s = queue[front];
        front++;
        printf("%i", s);
 
        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (int adjacent = 0; adjacent < g->v;
             adjacent++) {
            if (g->adj_matrix[s][adjacent] && !visited[adjacent]) {
                visited[adjacent] = true;
                queue[rear] = adjacent;
                rear++;
            }
        }
    }
}

int main(void)
{
    Graph* g = create_graph(4);
    Graph_addEdge(g, 0, 1);
    Graph_addEdge(g, 0, 2);
    Graph_addEdge(g, 1, 2);
    Graph_addEdge(g, 2, 0);
    Graph_addEdge(g, 2, 3);
    Graph_addEdge(g, 3, 3);
    Graph_print(g);
    //BFS starting from 2
    Graph_BFS(g, 2);
    destroy_graph(g);
    return 0;

}
