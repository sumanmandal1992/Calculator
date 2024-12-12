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

	int j=0;
	for (int i=0; i<len-1; i++) {
		j = i+1;
		if (isoperator(exp[i]) && isoperator(exp[j])) {
			if ((exp[i] == '/' || exp[i] == '*') && (exp[j] == '/' || exp[j] == '*')) {
				return false;
			}
		}
	}

	int ob = 0, cb = 0;
	for (int i=0; i<len; i++) {
		if (exp[i] == '(') {
			ob++;
		} else if (exp[i] == ')') {
			cb++;
		} else if (!isoperator(exp[i]) && !isdigit(exp[i]) && exp[i] != '(' && exp[i] != ')') {
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

	Stack *numbers = createstack();
	Stack *operators = createstack();
	char ob = '(';
	push(operators, &ob);
	for (int i=0; i<len; i++) {
		if (isoperator(exp[i])) {
			char curop = *((char*)peek(operators));
			if (curop == '(') {
				push(operators, &exp[i]);
				curop = *((char*)peek(operators));
			} else if (precedence(exp[i]) > precedence(curop)) {
				push(operators, &exp[i]);
				curop = *((char*)peek(operators));
			} else {
				while (curop != '(' && precedence(exp[i]) <= precedence(curop)) {
					char exop = *((char*)pop(operators));
					curop = *((char*)peek(operators));
					double b = *((double*)pop(numbers));
					double a = *((double*)pop(numbers));
					double *ans = (double*)malloc(sizeof(double));
					*ans = calc(exop, a, b);
					push(numbers, ans);
				}
				push(operators, &exp[i]);
			}
		} else if (exp[i] == '(') {
			push(operators, &exp[i]);
		} else if (exp[i] == ')') {
			char curop = *((char*)peek(operators));
			while (curop != '(') {
				char exop = *((char*)pop(operators));
				curop = *((char*)peek(operators));
				double b = *((double*)pop(numbers));
				double a = *((double*)pop(numbers));
				double *ans = malloc(sizeof(double));
				*ans = calc(exop, a, b);
				push(numbers, ans);
			}
			pop(operators);
		} else {
			int j=i, d=i, l=0;
			while (isdigit(exp[j])) {
				l++;
				j++;
			}
			char digit[l+1];
			for (int c=0; c<l; c++) {
				digit[c] = exp[d];
				d++;
			}
			digit[d] = '\0';

			double *n = malloc(sizeof(double));
			*n = atof(digit);
			push(numbers, n);

			j--;
			i = j;
		}
	}
	char curop = *((char*)peek(operators));
	while (curop != '(') {
		char exop = *((char*)pop(operators));
		curop = *((char*)peek(operators));
		double b = *((double*)pop(numbers));
		double a = *((double*)pop(numbers));
		double *ans = malloc(sizeof(double));
		*ans = calc(exop, a, b);
		push(numbers, ans);
	}
	pop(operators);

	double ans = *((double*)pop(numbers));

	clear_stack(operators);
	clear_stack(numbers);

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
