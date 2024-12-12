#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct List {
	void *data;
	struct List *next;
}List;

struct _Stack {
	List *top;
	List *node;
};

Stack *createstack() {
	Stack *st = (Stack *)malloc(sizeof(Stack));
	if(!st) return NULL;
	st->top = NULL;
	st->node = NULL;
	return st;
}

static List *createlist(void *data) {
	List *node = (List*) malloc(sizeof(List));
	if(!node) return NULL;
	node->data = data;
	node->next = NULL;
	return node;
}

static bool isempty(Stack *st) {
	if(st->top == NULL) return true;
	return false;
}

void push(Stack *st, void *data) {
	st->node = createlist(data);
	if(isempty(st)) st->top = st->node;
	else {
		st->node->next = st->top;
		st->top = st->node;
	}
}

void *pop(Stack *st) {
	void *data = NULL;
	if(isempty(st)) {
		printf("Stack underflow\n");
		exit(1);
	}
	data = st->top->data;
	List *node = st->top;
	st->top = st->top->next;
	free(node);
	return data;
}

void *peek(Stack *st) {
	return st->top->data;
}

void display(Stack *st, Type type) {
	List *node = st->top;
	while (node != NULL) {
		if(type == num) printf("%lf\n", *((double*)node->data));
		else if(type == op) printf("%c\n", *((char*)node->data));
		node = node->next;
	}
}

void clear_stack(Stack *st) {
	while (st->top != NULL) {
		pop(st);
	}
}
