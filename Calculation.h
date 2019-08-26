//Prototype declaration of functions.////////////////////////////////////////////////////////////////
#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__
int isOperand(char);
int prec(char);
double strtoD(char*);
int len(char*);
void operation(double*, int, char);
double pow(double, double);
void calculate(char*);
#endif
