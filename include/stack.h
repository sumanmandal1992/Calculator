#ifndef __STACK_H__
#define __STACK_H__
#define MAX 10

typedef enum stackchoice { dispop, dispnum } choice;

void pushop(char op);
void pushnum(double num);
char popop();
double popnum();
char peepop();
void display(choice ch);

#endif
