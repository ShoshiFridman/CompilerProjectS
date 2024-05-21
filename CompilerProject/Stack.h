#pragma once


#define MAX_SIZE 100

typedef struct Node {
	int state;
	char* key;
	int numOfToken;
	struct Node** pointers;
	int numPointers;
	struct Node* parent;
} Node;

typedef struct {
	Node* array[MAX_SIZE];
	int top;
} Stack;


Stack* createStack();
Node* createNode(int state, char* key, int numOfToken);
void   addPointer(Node* node, Node* pointer);


int   isFull(Stack* stack);
int   isEmpty(Stack* stack);
void  push(Stack* stack, Node* node);
Node* pop(Stack* stack);
Node* peekAt(Stack* stack, int position);
Node* peek(Stack* stack);
