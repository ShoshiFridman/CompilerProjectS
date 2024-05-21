
#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"
#include "mystring.h"


Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

struct Node* createNode(int state, char* key, int numOfToken) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Error: Memory allocation for node failed\n");
        exit(1); // Exit the program or handle the error accordingly
    }
    newNode->key = my_strdup(key); // העתקת המחרוזת כדי למנוע בעיות זיכרון
    if (newNode->key == NULL) {
        fprintf(stderr, "Error: Memory allocation for key failed\n");
        free(newNode);
        exit(1); // Exit the program or handle the error accordingly
    }
    newNode->numOfToken = numOfToken;
    newNode->state = state;
    newNode->numPointers = 0;
    newNode->pointers = NULL;
    return newNode;
}

void addPointer(Node* node, Node* pointer) {
    node->numPointers++;
    Node** temp = (Node**)realloc(node->pointers, node->numPointers * sizeof(Node*));
    if (temp == NULL) {
        fprintf(stderr, "Error: Memory reallocation for pointers failed\n");
        // You can choose to handle the error by freeing resources and exiting the program
        return;
    }
    node->pointers = temp;
    node->pointers[node->numPointers - 1] = pointer;
}


int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, Node* node) {
    if (isFull(stack)) {
        printf("Stack overflow\n");
        return;
    }
    stack->array[++stack->top] = node;
}

Node* pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        return NULL;
    }
    return stack->array[stack->top--];
}

Node* peekAt(Stack* stack, int position) {
    if (isEmpty(stack) || position < 1 || position > stack->top + 1) {
        printf("Invalid position or stack is empty\n");
        return NULL;
    }
    return stack->array[stack->top - position + 1];
}

Node* peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return NULL;
    }
    return stack->array[stack->top];
}
