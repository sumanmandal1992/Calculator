#ifndef __CALCULATION_H__
#define __CALCULATION_H__

int isOperand(char);
int prec(char);
double strtoD(char*);
int len(char*);
void operation(long double*, int, char);
double pow(double, double);
long double calculate(char*);

#endif
