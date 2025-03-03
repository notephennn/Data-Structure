#include <stdio.h> 
#include <stdlib.h> 

typedef struct Node{
    int data; 
    struct Node *next; 
    struct Node *prev; 
} Node; 

Node *createNode(int data){
    Node *newNode = (Node*)malloc(sizeof(Node)); 
    newNode->data = data; 
    newNode->next = NULL; 
    newNode->prev = NULL; 
    return newNode; 
}

void transverseForwardList(Node *head){
    Node *currentNode = head; 

    printf("Transverse Forward List: "); 
    while(currentNode != NULL ){
        printf("%d -> ", currentNode->data); 
        currentNode = currentNode->next; 
    }

    printf("NULL\n");
}

void backwardTransverseList(Node *tail){
    Node *currentNode = tail; 

    printf("Transverse Backward List: "); 
    while(currentNode != NULL){
        printf("%d -> ", currentNode->data); 
        currentNode = currentNode->prev; 
    }

    printf("NULL\n"); 
}

int main(){
    Node *node1 = createNode(1); 
    Node *node2 = createNode(2); 
    Node *node3 = createNode(3); 
    Node *node4 = createNode(4); 

    node1->next = node2; 

    node2->next = node3; 
    node2->prev = node1; 

    node3->next = node4; 
    node3->prev = node2; 

    node4->prev = node3; 

    transverseForwardList(node1); 

    backwardTransverseList(node4); 
}