#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define the Node structure
typedef struct
{
    // Priority of the node
    int priority;
    // Data contained in the node
    int data;
} Node;

// Define the PriorityQueue structure
typedef struct
{
    // Pointer to the array of elements
    Node *heap;
    // Maximum possible size of the priority queue
    int capacity;
    // Current number of elements in the priority queue
    int size;
} PriorityQueue;

// Function to create a new PriorityQueue
PriorityQueue *createPriorityQueue(int capacity)
{
    // Allocate memory for the PriorityQueue structure
    PriorityQueue *queue = malloc(sizeof(PriorityQueue));
    // Allocate memory for the array of elements or nodes
    queue->heap = malloc(capacity * sizeof(Node));
    // Set the current size to 0
    queue->capacity = capacity;
    // Return the newly created PriorityQueue
    queue->size = 0;
    return queue;
}

// Function to swap two nodes
void swap(Node *a, Node *b)
{
    // Temporary node to facilitate the swap
    Node temp = *a;
    // Swap the nodes
    *a = *b;
    *b = temp;
}
// Function to return the index of left child of a node in a heap
int left(int i)
{
    return 2 * i + 1;
}

// Function to return the index of right child of a node in a heap
int right(int i)
{
    return 2 * i + 2;
}
// function to return the index of parent of a node in a heap
int parent(int i)
{
    return (i - 1) / 2;
}

// Function to ensure the heap property is maintained
void max_heapify(PriorityQueue *queue, int i)
{
    // Index of left child
    int l = left(i);
    // Index of right child
    int r = right(i);
    // Initialize largest as root
    int largest = i;

    // If left child is larger than root
    if (l < queue->size && queue->heap[l].priority > queue->heap[largest].priority)
    {
        largest = l;
    }

    // If right child is larger than largest so far
    if (r < queue->size && queue->heap[r].priority > queue->heap[largest].priority)
    {
        largest = r;
    }

    // If smallest is not root
    if (largest != i)
    {
        // Swap the root with the largest child
        swap(&queue->heap[i], &queue->heap[largest]);
        // Recursively heapify the affected sub-tree
        max_heapify(queue, largest);
    }
}

// Function to add an element to the PriorityQueue
void enqueue(PriorityQueue *queue, int priority, int data)
{
    // If the PriorityQueue is full
    if (queue->size >= queue->capacity)
    {
        printf("Priority queue is full.\n");
        return;
    }
    // Create a new Node
    Node newNode;
    // Set the priority of the new Node
    newNode.priority = priority;
    // Set the data of the new Node
    newNode.data = data;
    // Get the index where the new Node will be inserted
    int i = queue->size;
    // Insert the new Node at the end of the PriorityQueue
    queue->heap[i] = newNode;

    // While the inserted node is not the root and its priority is less than its parent's priority
    while (i > 0 && queue->heap[i].priority > queue->heap[parent(i)].priority)
    {
        // Swap the node with its parent
        swap(&queue->heap[i], &queue->heap[parent(i)]);
        // Update the index to the parent's index
        i = parent(i);
    }
    // Increase the size of the PriorityQueue
    queue->size++;
}

// Function to remove and return the highest priority element from the PriorityQueue
Node dequeue(PriorityQueue *queue)
{
    // If the PriorityQueue is empty
    if (queue->size <= 0)
    {
        printf("Priority queue is empty.\n");
        // Create an empty Node
        Node emptyNode;
        // Set the priority to -1
        emptyNode.priority = -1;
        // Set the data to -1
        emptyNode.data = -1;
        // Return the empty Node
        return emptyNode;
    }
    // Get the root of the PriorityQueue
    Node root = queue->heap[0];
    // Replace the root with the last element in the PriorityQueue
    queue->heap[0] = queue->heap[queue->size - 1];
    // Decrease the size of the PriorityQueue
    queue->size--;
    // Heapify the PriorityQueue
    max_heapify(queue, 0);
    // Return the removed element
    return root;
}

// Function to print the PriorityQueue
void printPriorityQueue(PriorityQueue *queue)
{
    printf("Priority Queue: ");
    // For each element in the PriorityQueue
    for (int i = 0; i < queue->size; i++)
    {
        // Print the priority and data of the element
        printf("(%d, %d) ", queue->heap[i].priority, queue->heap[i].data);
    }
    printf("\n");
}
// free the memory allocated to the PriorityQueue
void freePriorityQueue(PriorityQueue *queue)
{
    free(queue->heap);
    free(queue);
}

int main()
{
    // Create a new PriorityQueue
    PriorityQueue *queue = createPriorityQueue(10);
    // Add elements to the PriorityQueue
    enqueue(queue, 3, 10);
    enqueue(queue, 1, 20);
    enqueue(queue, 2, 30);
    enqueue(queue, 5, 40);
    enqueue(queue, 4, 50);
    // Print the PriorityQueue
    printPriorityQueue(queue);

    // Remove the highest priority element from the PriorityQueue
    while (queue->size > 0)
    {
        Node node = dequeue(queue);
        printf("Dequeued: (%d, %d)\n", node.priority, node.data);
        // Print the PriorityQueue
        printPriorityQueue(queue);
    }
    // free the memory allocated to the PriorityQueue
    freePriorityQueue(queue);

    return 0;
}