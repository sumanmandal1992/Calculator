#ifndef __STACK_H__
#define __STACK_H__

typedef struct _Stack Stack;
typedef enum Type {num, op} Type;

Stack *createstack();
void push(Stack *st, void *data);
void *pop(Stack *st);
void *peek(Stack *st);
void display(Stack *st, Type type);
void clear_stack(Stack *st);

#endif
