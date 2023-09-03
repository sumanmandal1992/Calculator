#include "calculate.h"
#include "stack.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

static int precedence(char op) {
	switch (op) {
		case '^':
			return 20;
		case '/':
		case '*':
			return 19;
		case '+':
		case '-':
			return 18;
	}
	return -1;
}

static bool isoperator(char el) {
	switch (el) {
		case '(':
		case ')':
		case '^':
		case '/':
		case '*':
		case '+':
		case '-':
			return true;
	}
	return false;
}

double eval(char op, double num1, double num2) {
	double result = 0.0;
	switch(op) {
		case '+':
			result = num1+num2;
			break;
		case '-':
			result = num1-num2;
			break;
		case '*':
			result = num1*num2;
			break;
		case '/':
			result = num1/num2;
			break;
		case '^':
			result = pow(num1, num2);
			break;
	}
	return result;
}

double calculate(char *exp) {
	char *expm = NULL;
	if(exp[0] != '(') {
		expm = (char *)malloc(sizeof(exp)+2);
		expm[0] = '(';
		strcat(expm, exp);
		expm = (char*)realloc(expm, sizeof(expm)+2);
		strcat(expm, ")");
	}

	int i = 0, j = 0;
	char ch, curop, num[20];
	while((ch = expm[i++]) != '\0') {
		j = 0;
		if(isoperator(ch)) {
			if(ch == '(') pushop(ch);
			else if(ch == ')') while((curop = popop()) != '(') pushnum(eval(curop, popnum(), popnum()));
			else if(precedence(ch) > precedence(topop())) pushop(ch);
			else if(precedence(ch) <= precedence(topop())) {
				while(precedence(ch) <= precedence(topop())) pushnum(eval(popop(), popnum(), popnum()));
				pushop(ch);
			}
		}
		else if (ch == ' ') continue;
		else {
			num[j++] = ch;
			while(!isoperator(ch = expm[i++])) num[j++] = ch;
			i--;
			num[j] = '\0';
			pushnum(atof(num));
		}
	}

	free(expm);

	return popnum();
}
