/*
I will implement AVL trees where basic operations like insertion, deletion, and searching 
can be done in O(log n) time. 
*/

#include <stdio.h>
#include <stdlib.h>

// This is the no.of nodes in the tree
int n;
// define the node
typedef struct Node
{
    int key;
    struct Node *right;
    struct Node *left;
    struct Node *back;
    
} Node;

// function prototypes
Node* create_node(int key);
void insert(Node **root, int key);
int get_balance_factor(Node *node);
Node *get_unbalanced_subtree_root(Node *node, Node *root);
Node* right_rotate(Node *y);
Node* left_rotate(Node *x);
void inorder_print_tree(Node *root);
Node* balance(Node *node, int key);

int main(void)
{
    // Prompt the user for input
    printf("Please enter the size of the tree: ");
    // Read the integer input and store it in the variable Size
    scanf("%d", &n);
    // intialize the root node
    Node *root = NULL;

    // Ask for key and insert the nodes
    int key;
    for(size_t i = 0; i < n; i++)
    {
        // prompt for the key
        printf("Enter the key: ");
        // store the key
        scanf("%d", &key);

        // insert the node and balance it
        insert(&root, key);

    }
    // Print in-order traversal (should be sorted)
    printf("In-order traversal: ");
    inorder_print_tree(root);
    printf("\n");
}


// create a node
Node* create_node(int key)
{
    Node *node = malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->back = NULL;
    return node;
}
// get height(max no.of edges) of left and right subtree of any node
int get_subtree_height(Node *node)
{
    if(node == NULL)
    {
        return 0;
    }
    // get recursively the height of left subtree
    int left_height = get_subtree_height(node->left);
     // get recursively the height of right subtree
    int right_height = get_subtree_height(node->right);
    // return the maximumm of the two, +1 for the edge from root to the subtree
    return 1 + left_height > right_height ? left_height : right_height;
}

void insert(Node **root, int key)
{
    // insert the first root node
    if (*root == NULL) {
        *root = create_node(key);
        return;
    }
    Node *node = create_node(key);
    Node *current = *root;
    Node *parent = NULL;
    // current != NULL is the condition to find an empty spot
    while(current != NULL)
    {
        // update the parent
        parent = current;
        // go left
        if(key < current->key)
        {
            
            current = current->left;
        }
        // go right
        else if(key > current->key)
        {
            current = current->right;
        }
        // equal keys cannot be inserted in a binary tree hence do not insert
        else
        {
            free(node);
            return;
        }
    }
    // Insert the node when while loop ends(empty spot found)
    if (key < parent->key)
    {
        parent->left = node;
    }
    else if(key > parent->key)
    {
        parent->right = node;
    }
    // make a back connection to the parent
    node->back = parent;
    // get the root of the unbalanced subtree after inserting the current node
    // by backtracking from current node to root
    Node* unbalanced_node = get_unbalanced_subtree_root(node, *root);
    // Balance the tree if unbalanced node exists, do nothing if it does not exist
    if (unbalanced_node != NULL) {
        // update the root after balancing
        *root = balance(unbalanced_node, key);
    }
    return;
}
// get balance factor of any node
int get_balance_factor(Node *node)
{
    if(node == NULL)
    {
        return 0;
    }
    return get_subtree_height(node->left) - get_subtree_height(node->right);

}


Node *get_unbalanced_subtree_root(Node *node, Node *root)
{
    Node *current = node;

    while(current != NULL)
    {
        // get the balance factor of current node
        int bf = get_balance_factor(current);
        // only bf of 1, 0 and -1 are allowed
        if(bf > 1 || bf < -1)
        {
            return current;
        }
        // else go back to parent node until the root node
        current = current->back;
    }
    // can't find an unbalanced node
    return NULL;
}
// Right rotate subtree rooted with y
Node* right_rotate(Node *y) 
{
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update back pointers
    if (T2 != NULL) T2->back = y;
    x->back = NULL;
    y->back = x;

    // Return new root
    return x;
}


// Left rotate subtree rooted with x
Node* left_rotate(Node *x) 
{
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update back pointers
    if (T2 != NULL) T2->back = x;
    y->back = NULL;
    x->back = y;

    // Return new root
    return y;
}
// the function takes in input the unbalanced node and the key of the node being inserted
Node* balance(Node *node, int key)
{
    int bf = get_balance_factor(node);
    // left left case
    if(bf > 1 &&  key < node->left->key)
    {
        // rotate right with respect to unbalanced node
        Node *new_root = right_rotate(node);
        return new_root;
    }
    // right right case
    if (bf < -1 && key > node->right->key) 
    {
        // rotate right with respect to unbalanced node
        Node *new_root = left_rotate(node);
        return new_root;
    }
     // Left Right Case
    if (bf > 1 && key > node->left->key) {
        // first left rotate with respect to left child of unbalanced node
        node->left = left_rotate(node->left);
        // Then right rotate with respect to unbalanced node
        Node *new_root = right_rotate(node);
        return new_root;
    }
    // Right Left Case
    if (bf < -1 && key < node->right->key) {
        // first left rotate with respect to right child of unbalanced node
        node->right = right_rotate(node->right);
        // Then left rotate with respect to unbalanced node
        Node *new_root = left_rotate(node);
        return new_root;
    }
    return node;

}


void inorder_print_tree(Node *root)
{
    if (root != NULL)
    {
        inorder_print_tree(root->left);
        printf("Key: %d\n", root->key);
        inorder_print_tree(root->right);
    }
}

