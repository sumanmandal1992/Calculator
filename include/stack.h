#ifndef __STACK_H__
#define __STACK_H__

typedef struct _Stack Stack;
typedef enum _Type{num, op} Type;

Stack *create_stack();
void push(Stack *st, void *data);
void *pop(Stack *st);
void *peek(Stack *st);
void display(Stack *st, Type t);
void free_stack(Stack *st);

#endif
