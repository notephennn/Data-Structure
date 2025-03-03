#include <stdio.h> 
#include <stdlib.h> 

typedef struct Node{
    int data; 
    struct Node *next; 
} Node; 

// fungsi buat nambahin node baru 
Node *createNode(int data){
    Node *newNode = (Node*)malloc(sizeof(Node)); 
    newNode->data = data; 
    newNode->next = NULL; 
    return newNode; 
}

void printList(Node *head){
    Node *currentNode = head; 
    while ( currentNode != NULL){
        printf("%d -> ", currentNode->data); 
        currentNode = currentNode->next; 
    }

    printf("NULL\n"); 
}

int main(){
    Node *node1 = createNode(3); 
    Node *node2 = createNode(5); 
    Node *node3 = createNode(8); 
    Node *node4 = createNode(10); 

    node1->next = node2; 
    node2->next = node3; 
    node3->next = node4; 
    
    printList(node1); 
}