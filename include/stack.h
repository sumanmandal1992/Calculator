#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef union _Info
{
	char operator;
	double number;
}Info;

typedef struct _Stack
{
	bool isOperator;
	Info *info;
	struct _Stack *next;
}Stack;


Stack *newStack(void);
void push(Stack **top, Info *info, bool isOperator);
void pop(Stack **top);
void display(Stack *top);


#endif
