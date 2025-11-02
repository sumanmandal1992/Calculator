#include "parseexp.h"
#include "stack.h"
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

static void eatspace(char *exp)
{
	int i=0, j=0;
	while(exp[i] != '\0')
		if(exp[i] == ' ')
			exp[j] = exp[++i];
		else
			exp[j++] = exp[i++];
	exp[j] = '\0';
}

static int precedence(char op)
{
	switch(op) {
		case '^':
			return 20;
		case '*':
		case '/':
			return 19;
		case '+':
		case '-':
			return 18;
		default:
			return -1;
	}
}

static bool isoperator(char chr) {
	switch (chr) {
		case '^':
		case '*':
		case '/':
		case '%':
		case '+':
		case '-':
			return true;
	}
	return false;
}

static bool isvalid(char *exp) {
	int len = strlen(exp);

	if (exp[0] == '/' || exp[0] == '*') {
		return false;
	}

	for (int i=0; i<len-1; i++) {
		if (isoperator(exp[i]) && isoperator(exp[i+1])) return false;
	}

	int ob = 0, cb = 0;
	for (int i=0; i<len; i++) {
		if (exp[i] == '(') {
			ob++;
		} else if (exp[i] == ')') {
			cb++;
		} else if (!isoperator(exp[i]) && !isdigit(exp[i]) && exp[i] != '(' && exp[i] != ')' && exp[i] != '.') {
			return false;
		}
	}
	if (ob != cb) {
		return false;
	}

	return true;
}

static double calc(char op, double a, double b) {
	switch (op) {
		case '^':
			return pow(a, b);
		case '*':
			return a*b;
		case '/':
			return a/b;
		case '+':
			return a+b;
		case '-':
			return a-b;
	}
	return -0.0;
}

double evaluate(char *exp) {
	int len = strlen(exp);
	eatspace(exp);
	if (!isvalid(exp)) {
		printf("Invalid expression.\n");
		exit(1);
	}

	Stack *num = create_stack();
	Stack *op = create_stack();
	push(op, "(");
	for (int i=0; i<len; i++) {
		if (isoperator(exp[i])) {
			if (peek(op) == NULL) push(op, &exp[i]);
			else if (precedence(*(char*)peek(op)) < precedence(exp[i])) push(op, &exp[i]);
			else {
				while(precedence(*((char*)peek(op))) >= precedence(exp[i])) {
					char o = *(char*)pop(op);
					double n2 = *(double*)pop(num);
					double n1 = *(double*)(char*)pop(num);
					double r = calc(o, n1, n2);
					push(num, (void*)&r);
					printf("---- %lf ----\n", r);
				}
				push(op, &exp[i]);
			}
		} else if (exp[i] == '(') {
			push(op, &exp[i]);
		} else if (exp[i] == ')') {
			while (*(char*)peek(op) != '(') {
				char o = *(char*)pop(op);
				double b = *(double*)pop(num);
				double a = *(double*)pop(num);
				double r = calc(o, a, b);
				push(num, (void*)&r);
			}
			pop(op);
		} else {
			int j=i, d=i, l=0;
			while (isdigit(exp[j]) || exp[j] == '.') {
				l++;
				j++;
			}
			char digit[l+1];
			for (int c=0; c<l; c++) {
				digit[c] = exp[d];
				d++;
			}
			digit[d] = '\0';

			double *n = (double*)malloc(sizeof(double));
			*n = atof(digit);
			push(num, (void*)n);
			j--;
			i = j;
		}
	}
	char curop = *(char*)peek(op);
	while (curop != '(') {
		char exop = *(char*)pop(op);
		curop = *(char*)peek(op);
		double b = *(double*)pop(num);
		double a = *(double*)pop(num);
		double ans = calc(exop, a, b);
		push(num, (void*)&ans);
	}
	pop(op);

	double ans = *(double*)pop(num);

	free_stack(op);
	free_stack(num);

	return ans;
}

void print(double result) {
  if (round(result * 10000000000) / 10000000000 < result ||round(result * 10000000000) / 10000000000 > result)
    printf("Result: %.10lf\n", result);
  else if (round(result * 1000000000) / 1000000000 < result || round(result * 1000000000) / 1000000000 > result)
    printf("Result: %.9lf\n", result);
  else if (round(result * 10000000) / 10000000 < result || round(result * 10000000) / 10000000 > result)
    printf("Result: %.8lf\n", result);
  else if (round(result * 1000000) / 1000000 < result || round(result * 1000000) / 1000000 > result)
    printf("Result: %.7lf\n", result);
  else if (round(result * 100000) / 100000 < result || round(result * 100000) / 100000 > result)
    printf("Result: %lf\n", result);
  else if (round(result * 10000) / 10000 < result || round(result * 10000) / 10000 > result)
    printf("Result: %.5lf\n", result);
  else if (round(result * 1000) / 1000 < result || round(result * 1000) / 1000 > result)
    printf("Result: %.4lf\n", result);
  else if (round(result * 100) / 100 < result || round(result * 100) / 100 > result)
    printf("Result: %.3lf\n", result);
  else if (round(result * 10) / 10 < result || round(result * 10) / 10 > result)
    printf("Result: %.2lf\n", result);
  else if (round(result) > result || round(result) < result)
    printf("Result: %.1lf\n", result);
  else
    printf("Result: %.0lf\n", result);
}
