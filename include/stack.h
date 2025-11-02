#ifndef __STACK_H__
#define __STACK_H__

typedef struct _Stack Stack;

Stack *create_stack();
void push(Stack *st, void *data);
void *pop(Stack *st);
void *peek(Stack *st);
void display(Stack *st);
void free_stack(Stack *st);

#endif
