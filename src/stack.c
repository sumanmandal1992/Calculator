#include "stack.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef union {
  double num;
  char op;
} el;

typedef struct _Stack {
  el *elem;
  struct _Stack *next;
} Stack;

static Stack *topop = NULL;
static Stack *topnum = NULL;

static bool isemptyop() {
  if (topop == NULL)
    return true;
  return false;
}

static bool isemptynum() {
  if (topnum == NULL)
    return true;
  return false;
}

static Stack *create() {
  Stack *tmp = (Stack *)malloc(sizeof(Stack));
  tmp->next = NULL;
  tmp->elem = (el *)malloc(sizeof(el));
  tmp->elem->num = 0.0;
  return tmp;
}

void pushop(char op) {
  Stack *tmp = create();
  tmp->elem->op = op;
  if (isemptyop())
    topop = tmp;

  else {
    tmp->next = topop;
    topop = tmp;
  }
}

void pushnum(double num) {
  Stack *tmp = create();
  tmp->elem->num = num;

  if (isemptynum())
    topnum = tmp;
  else {
    tmp->next = topnum;
    topnum = tmp;
  }
}

char popop() {
  if (isemptyop())
    return '\0';
  char op = topop->elem->op;
  Stack *tmp = topop;
  topop = topop->next;
  free(tmp->elem);
  free(tmp);
  return op;
}

double popnum() {
  if (isemptynum())
    return -0.0;
  double num = topnum->elem->num;
  Stack *tmp = topnum;
  topnum = topnum->next;
  free(tmp->elem);
  free(tmp);
  return num;
}

char peepop() {
  if (isemptyop())
    return '\0';
  return topop->elem->op;
}

void display(choice ch) {
  Stack *tmp = NULL;
  if (ch == opstack) {
    tmp = topop;
    while (tmp != NULL) {
      printf("%c\n", tmp->elem->op);
      tmp = tmp->next;
    }
    printf("\n");
  } else if (ch == numstack) {
    tmp = topnum;
    while (tmp != NULL) {
      printf("%lf\n", tmp->elem->num);
      tmp = tmp->next;
    }
    printf("\n");
  }
}
