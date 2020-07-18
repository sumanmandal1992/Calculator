#include "Stack.h"

//Creation of stack.//////////////////////////////////////////////////
Stack *createStack(unsigned capacity){
Stack *stack = (Stack*)malloc(sizeof(Stack));
if(!stack)
return NULL;

stack->top = -1;
stack->capacity = capacity;

stack->array = (char*)malloc(stack->capacity * sizeof(char));
if(!stack->array)
return NULL;

return stack;
}

//Push a element into stack.//////////////////////////////////////////
void push(Stack *stack, char operator){
stack->array[++stack->top] = operator;
}

//Delete a element from stack.////////////////////////////////////////
char pop(Stack *stack){
if(!isEmpty(stack))
return stack->array[stack->top--];
return '$';
}

//Check stack, is it empty or not.///////////////////////////////////
int isEmpty(Stack *stack)
{
return stack->top==-1;
}

//Peek a element from stack.////////////////////////////////////////
char peek(Stack *stack){
return stack->array[stack->top];
}

