#include <stdio.h> 
#include <stdlib.h> 

typedef struct Tree {
    int data; 
    struct Tree *left; 
    struct Tree *right; 
} Tree;

Tree *createTree(int data){
    Tree *newTree = (Tree*)malloc(sizeof(Tree)); 
    newTree->data = data; 
    newTree->left = NULL; 
    newTree->right = NULL;

    return newTree; 
}

Tree *insertNode(Tree *root, int data){
    if ( root == NULL ) return createTree(data); 
    if ( data < root->data ) root->left = insertNode(root->left, data); 
    else root->right = insertNode(root->right, data);

    return root;  
}

void inOrderTraversal(Tree *newTree) {
    if (newTree == NULL)
    return;

    inOrderTraversal(newTree->left);
    printf("%d", newTree->data);
    
    if (newTree->left)
        printf(" (Left: %d)", newTree->left->data);
    else
        printf(" (Left: NULL)");
    
    if (newTree->right)
        printf(" (Right: %d)", newTree->right->data);
    else
        printf(" (Right: NULL)");
    
    printf("\n");
    inOrderTraversal(newTree->right);    
}

int main() {
    // Array of values to insert
    int values[] = {13, 7, 15, 3, 8, 14, 19, 18};
    int n = sizeof(values) / sizeof(values[0]);
    
    // Construct BST
    Tree *root = NULL;
    for (int i = 0; i < n; i++) {
        root = insertNode(root, values[i]);
    }

    // Traverse the tree
    printf("In-order Traversal: ");
    inOrderTraversal(root);
    printf("\n");

    return 0;
}