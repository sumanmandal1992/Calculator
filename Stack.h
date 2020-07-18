#include<stdlib.h>

//Define stack using structure.//////////////////////////////////////////////////////////////////////
typedef struct Stack
{
int top;
unsigned capacity;
char *array;
}Stack;

//Prototype declaration of functions.////////////////////////////////////////////////////////////////
Stack *createStack(unsigned);
void push(Stack*, char);
char pop(Stack*);
int isEmpty(Stack*);
char peek(Stack*);
