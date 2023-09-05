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
		default:
			return -0.000000;
	}
	return result;
}

double calculate(char *exp) {
	char *expm = NULL;
	
	expm = (char *)malloc(sizeof(char)*strlen(exp)+2);
	expm[0] = '(';
	expm[1] = '\0';
	strcat(expm, exp);
	expm = (char*)realloc(expm, sizeof(char)*strlen(expm)+2);
	strcat(expm, ")");

	int i = 0, j = 0;
	char ch, curop, num[20];
	while((ch = expm[i++]) != '\0') {
		j = 0;
		if(isoperator(ch)) {
			if(ch == '(') pushop(ch);
			else if(ch == ')') while((curop = popop()) != '(') {
				double ev = eval(curop, popnum(), popnum());
				if(ev == -0.0) {
					free(expm);
					printf("Invalid expression...\n");
					exit(1);
				}
				pushnum(ev);
			}
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
	if(popop() != '\0') {
		while(popop() != '\0');
		while(popnum() != -0.0);
		printf("Invalid expression...\n");
		exit(1);
	}

	return popnum();
}
