#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _Node {
	void *data;
	struct _Node *next;
}Node;

struct _Stack {
	Node *top;
	Node *node;
};

Stack *create_stack() {
	Stack *st = (Stack *)malloc(sizeof(Stack));
	if(!st) return NULL;
	st->top = NULL;
	st->node = NULL;
	return st;
}

static Node *create_node(void *data) {
	Node *node = (Node*) malloc(sizeof(Node));
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
	Node *tmp = create_node(data);
	if(!tmp) {
		printf("Failed to create node...\n");
		return;
	}
	if(isempty(st)) st->top = tmp;
	else {
		tmp->next = st->top;
		st->top = tmp;
	}
}

void *pop(Stack *st) {
	if(isempty(st)) {
		printf("Stack underflow\n");
		return NULL;
	}
	Node *tmp = st->top;
	st->top = st->top->next;
	void *data = tmp->data;
	free(tmp);
	return data;
}

void *peek(Stack *st) {
	if (isempty(st)) return NULL;
	return st->top->data;
}

void display(Stack *st) {
	Node *tmp = st->top;
	while (tmp != NULL) {
		printf("%lf\n", *(double*)tmp->data);
		tmp = tmp->next;
	}
}

void free_stack(Stack *st) {
	Node *tmp;
	while (st->top != NULL) {
		tmp = st->top;
		st->top = st->top->next;
		free(tmp);
	}
}
