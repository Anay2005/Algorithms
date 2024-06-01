/*
I will implement binary tree operations: Search, Insert, Delete Min, Max, Successor and predecessor all run in O(h) time, where h
is the height of the tree
*/

#include <stdio.h>
#include <stdlib.h>

// Declare the integer variable globally
int n;

// make a node, remeber to inculde back pointer to the parent node
typedef struct Node
{
    struct Node *left;
    struct Node *right;
    struct Node *back;

    int key;
    int data;

} Node;

// function prototypes
void insert(Node *node, Node **root);
void preorder_print_tree(Node *root);
void inorder_print_tree(Node *root);
void post_order_print_tree(Node *root);
Node* recursive_tree_search(Node *root, int key);
Node* iterative_tree_search(Node **root, int key);
Node* tree_min(Node **root);
Node* tree_max(Node **root);
Node* successor(Node *node, Node *root);
Node* predecessor(Node *node, Node *root);
Node* delete(Node *root, int key);

int main(void)
{

    // Prompt the user for input
    printf("Please enter the size of the tree: ");

    // Read the integer input and store it in the variable Size
    scanf("%d", &n);

    // Allocate memory for 'n' pointers to Node
    Node *node[n];
    // Initialize the root pointer
    Node *root = NULL;
    // create a tree
    for (int i = 0; i < n; i++)
    {
        printf("\n\n");
        // Allocate memory for each node
        node[i] = malloc(sizeof(Node));

        int key;
        int value;
        // Prompt the user for data
        printf("Please enter data: ");
        // Read the  data and then store it in the node
        scanf("%d", &value);

        // Prompt the user for key
        printf("Please enter key: ");
        // Read the key and then store it in the node
        scanf("%d", &key);

        node[i]->data = value;
        node[i]->key = key;
        // insert the node
        insert(node[i], &root);
    }
    printf("\n\n");

    // print the tree in preorder fashion before deletion
    printf("Preorder traversal is: \n");
    preorder_print_tree(root);
    printf("\n\n");

    // print the tree in inorder fashion before deletion
    printf("Inorder traversal before deletion is: \n");
    inorder_print_tree(root);
    printf("\n\n");

    // print the tree in post order fashion before deletion
    printf("Postorder traversal is: \n");
    post_order_print_tree(root);
    printf("\n\n");

    // Ask for the value to search before deletion
    int key_to_be_found;
    printf("Enter the key to search: ");
    scanf("%d", &key_to_be_found);
    printf("\n\n");
    // search for the key and data(aka node) recursively
    Node *searched_node_recursive = recursive_tree_search(root, key_to_be_found);
    // check if key was found and print it
    if (searched_node_recursive != NULL)
    {
        printf("The key was found recursively and is: %d\n with data: %d\n", searched_node_recursive->key, searched_node_recursive->data);
    }
    else
    {
        printf("The key was not found recursively\n");
    }
    printf("\n\n");

    // implement iterative search
    Node *searched_node_iterative = iterative_tree_search(&root, key_to_be_found);
    // check if key was found and print it
    if (searched_node_iterative != NULL)
    {
        printf("The key was found iteratively and is: %d\n with data: %d\n", searched_node_iterative->key, searched_node_iterative->data);
    }
    else
    {
        printf("The key was not found iteratively\n");
    }

    printf("\n\n");
    // get the min key of the tree
    Node *min_key = tree_min(&root);

    // print the min key
    if (min_key != NULL)
    {
        printf("The min of the tree is: %d\n", min_key->key);
    }
    else
    {
        printf("The min key of the tree was not found \n");
    }
    printf("\n\n");

    // get the min key of the tree
    Node *max_key = tree_max(&root);
    // print the max key
    if (max_key != NULL)
    {
        printf("The max of the tree is: %d\n", max_key->key);
    }
    else
    {
        printf("The max key of the tree was not found \n");
    }
    printf("\n\n");


    // get a successor of any node
    Node *suc = successor(node[0], root);
    // print the successor
    if(suc != NULL)
    {
        printf("The successor is key: %d data: %d\n", suc->key, suc->data);
    }
    else
    {
        printf("Successor is not found\n");

    }
    printf("\n\n");
    // Get the predecessor of node 
    Node *pred = predecessor(node[0], root);
    // Print the predecessor
    if (pred != NULL)
    {
        printf("The predecessor has key : %d data: %d\n", pred->key, pred->data);
    }
    else
    {
        printf("Predecessor is not found\n");
    }
    printf("\n\n");

    // Delete a node
    printf("Enter the key to delete: ");
    printf("\n\n");
    int key_to_delete;
    scanf("%d", &key_to_delete);
    // update the root of the tree after an element is deleted. Root may or may not change.
    root = delete(root, key_to_delete);

    printf("\n\n");
    // Print the tree in inorder fashion after deletion
    printf("Inorder traversal after deletion is: \n");
    inorder_print_tree(root);
    printf("\n\n");

    

    return 0;
}
// root points to root(this root pointer points to node initially memory address 0x000 declared in main)
void insert(Node *node, Node **root)
{
    // keep track of the current node
    Node *current = *root;
    // intialize the first node
    if (*root == NULL)
    {
        node->left = NULL;
        node->right = NULL;
        node->back = NULL;
        // root points to the first node which is the parent node never change this otherwise tree will be lost
        *root = node;

        return;
    }
    // use a traverse node for comparison
    Node *tra = *root;

    // Traverse to the correct spot to insert the node
    while (tra != NULL)
    {
        // Keep track of the current node
        current = tra; 
        if (node->key < tra->key)
        {
            tra = tra->left;
        }
        else
        {
            tra = tra->right;
        }
    }

    // Insert the node at the correct spot
    if (node->key < current->key)
    {
        current->left = node;
    }
    else
    {
        current->right = node;
    }
    node->back = current;
    node->left = NULL;
    node->right = NULL;
    return;
}

void preorder_print_tree(Node *root)
{
    if (root != NULL)
    {
        printf("Key: %d, Data: %d\n", root->key, root->data);
        preorder_print_tree(root->left);
        preorder_print_tree(root->right);
    }
}
void inorder_print_tree(Node *root)
{
    if (root != NULL)
    {
        inorder_print_tree(root->left);
        printf("Key: %d, Data: %d\n", root->key, root->data);
        inorder_print_tree(root->right);
    }
}

void post_order_print_tree(Node *root)
{
    if (root != NULL)
    {
        post_order_print_tree(root->left);
        post_order_print_tree(root->right);
        printf("Key: %d, Data: %d\n", root->key, root->data);
    }
}

Node* recursive_tree_search(Node *root, int key)
{
    if (root == NULL || key == root->key)
    {
        return root;
    }
    if (key < root->key)
    {
        return recursive_tree_search(root->left, key);
    }
    return recursive_tree_search(root->right, key);
}

Node* iterative_tree_search(Node **root, int key)
{
    Node *current = *root;
    while (current != NULL && key != current->key)
    {
        if (key < current->key)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return current;
}

Node* tree_min(Node **root)
{
    Node *current = *root;

    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

Node* tree_max(Node **root)
{
    Node *current = *root;

    while (current->right != NULL)
    {
        current = current->right;
    }
    return current;
}

Node* successor(Node *node, Node *root)
{
    // When right subtree exists the leftmost node of the right subtree is the successor
    if(node->right != NULL)
    {
        return tree_min(&(node->right));
    }
    else if(node == root)
    {
        return NULL;
    }
    else
    {
        Node *tra = node;
        Node *parent = node->back;
        // Traverse till the current node is towards the left of parent, the succesoor is the parent when loop stops
        while(tra != parent->left && parent != NULL)
        {
            tra = tra->back;
            parent = tra->back;
    
        }
        return parent;
    }

}

Node* predecessor(Node *node, Node *root)
{   
    // The predecessor is the rightmost node of the left subtree
    if (node->left != NULL)
    {
        return tree_max(&(node->left));
    }
    else if(root == node)
    {
        return NULL;
    }
    else
    {
        Node *tra = node;
        Node *parent = node->back;

        while (parent != NULL && tra != parent->right)
        {
            // same logic as successor stated differently
            tra = parent;
            parent = parent->back;
        }

        return parent;
    }
}

// A copy of root node is the argument and we are going to return that copy to main
Node* delete(Node *root, int key)
{
    // When there is no tree simply return
    if(root == NULL)
    {
        return root;
    }
    // check which subtree the key corresponds to
    else if(key < root->key)
    {
       root->left = delete(root->left, key);
    }
    else if(key > root->key)
    {
        root->right = delete(root->right, key);
    }

    // Actual delete logic when the key is equal to root->key
    else
    {
        // case 1: no child, leaf node can be simply deleted
        if(root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;

        }
        // case 2: one child delete the node by connecting its parent to its child
        else if(root->left == NULL)
        {
            Node *tmp = root;
            root = root->right;
            root->back = tmp->back;
            free(tmp);
        }
        else if(root->right == NULL)
        {
            Node *tmp = root;
            root = root->left;
            root->back = tmp->back;
            free(tmp);
        }
        // case 3: 2 children delete by finding the leftmost element in right subtree of the node and then replace the node 
        // with that element and erase the element with no left child(min element).
        else
        {
            Node *tmp = tree_min(&(root->right));
            root->key = tmp->key;
            root->right = delete(root->right, tmp->key);
        }
    }
    return root;
}