#include "validate.h"
#include <stdio.h>


bool isValidExp(char *exp)
{
	int parenthesis = 0, pos = 0;

	while(exp[pos] != '\0') {
		switch(exp[pos]) {
			case '(':
				++parenthesis;
				break;
			case ')':
				--parenthesis;
				break;
			case '.':
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '+':
			case '-':
			case '/':
			case '*':
			case '^':
				break;
			default:
				return false;
		}

		if((isDigit(exp[pos]) || exp[pos] == '(') && isOperator(exp[pos+1]) && isOperator(exp[pos+2])) {
			if((exp[pos+1] == '*' || exp[pos+1] == '/' || exp[pos+1] == '^') && (exp[pos+2] == '*' || exp[pos+2] == '/' || exp[pos+2] == '^'))
				return false;
			else if((exp[pos+1] == '+' || exp[pos+1] == '-') && (exp[pos+2] == '*' || exp[pos+2] == '/' || exp[pos+2] == '^'))
				return false;
			else if(exp[pos+2] == ')' && exp[pos+1] != ')')
				return false;
		}

		if(isOperator(exp[pos]) && isOperator(exp[pos+1]) && isOperator(exp[pos+2])) {
			if(
					(exp[pos] == '*' ||  exp[pos] == '/' ||  exp[pos] == '^' ||  exp[pos] == '+' ||  exp[pos] == '-') && 
					(exp[pos+1] == '*' ||  exp[pos+1] == '/' ||  exp[pos+1] == '^' ||  exp[pos+1] == '+' ||  exp[pos+1] == '-') && 
					(exp[pos+2] == '*' ||  exp[pos+2] == '/' ||  exp[pos+2] == '^' ||  exp[pos+2] == '+' ||  exp[pos+2] == '-')
				)
				return false;
		}


		pos++;
	}

	if(parenthesis == 0)
		return true;
	else 
		return false;

	return true;
}


bool isOperator(char symbol)
{
	switch(symbol) {
		case '(':
		case ')':
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
			return true;
	}
	return false;
}

bool isDigit(char ch)
{
	switch(ch) {
		case '.':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return true;
	}
	return false;
}

