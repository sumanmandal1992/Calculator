#include "stack.h"
#include <stdlib.h>
#include <stdbool.h>

typedef union {
	double num;
	char op;
}el;

typedef struct _Node{
	el *elem;
	struct _Node *next;
}OpStack, NumStack;


static OpStack *ophead = NULL;
static NumStack *numhead = NULL;

static bool isemptyop() {
	if(ophead == NULL) return true;
	return false;
}

static bool isemptynum() {
	if(numhead == NULL) return true;
	return false;
}

static struct _Node *create() {
	struct _Node *tmp = (struct _Node *)malloc(sizeof(struct _Node));
	tmp->next = NULL;
	tmp->elem = (el*)malloc(sizeof(el)) ;
	tmp->elem->num = 0.0;
	return tmp;
}

void pushop(char op) {
	OpStack *tmp = create();
	tmp->elem->op = op;
	if(isemptyop()) ophead = tmp;

	else {
		tmp->next = ophead;
		ophead = tmp;
	}
}

void pushnum(double num) {
	NumStack *tmp = create();
	tmp->elem->num = num;

	if(isemptynum()) numhead = tmp;
	else {
		tmp->next = numhead;
		numhead = tmp;
	}
}

char popop() {
	if(isemptyop()) return '\0';
	char op = ophead->elem->op;
	OpStack *tmp = ophead;
	ophead = ophead->next;
	free(tmp->elem);
	free(tmp);
	return op;
}

double popnum() {
	if(isemptynum()) return -0.000000;
	double num = numhead->elem->num;
	NumStack *tmp = numhead;
	numhead = numhead->next;
	free(tmp->elem);
	free(tmp);
	return num;
}

char topop() {
	if(isemptyop()) return '\0';
	return ophead->elem->op;
}

void display(choice ch) {
	struct _Node *tmp = NULL;
	if(ch == dispop) {
		tmp = ophead;
		while(tmp != NULL) {
			printf("%c\n", tmp->elem->op);
			tmp = tmp->next;
		}
		printf("\n");
	} else if(ch == dispnum) {
		tmp = numhead;
		while(tmp != NULL) {
			printf("%lf\n", tmp->elem->num);
			tmp = tmp->next;
		}
		printf("\n");
	}

}
