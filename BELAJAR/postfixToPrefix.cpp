#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack structure
char stack[MAX][MAX];
int top = -1;

// Function to check if character is operator
int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Function to push an element to stack
void push(char* str) {
    if (top < MAX - 1) {
        strcpy(stack[++top], str);
    }
}

// Function to pop an element from stack
void pop(char* str) {
    if (top >= 0) {
        strcpy(str, stack[top--]);
    }
}

// Function to convert postfix to prefix
void postfix_to_prefix(char* postfix, char* prefix) {
    int len = strlen(postfix);
    int k = 0;

    // Read postfix from right to left
    for (int i = len - 1; i >= 0; i--) {
        if (is_operator(postfix[i])) {
            char operand1[MAX], operand2[MAX];
            pop(operand1);
            pop(operand2);
            
            // Create a prefix expression by combining operator and operands
            sprintf(prefix, "%c%s%s", postfix[i], operand1, operand2);
            push(prefix);
        } else {
            char operand[2] = {postfix[i], '\0'};
            push(operand);
        }
    }

    // The final result is stored in the stack top
    strcpy(prefix, stack[top]);
}

int main() {
    char postfix[MAX], prefix[MAX];

    printf("Enter postfix expression: ");
    scanf("%s", postfix);

    postfix_to_prefix(postfix, prefix);

    printf("Prefix expression: %s\n", prefix);
    return 0;
}
