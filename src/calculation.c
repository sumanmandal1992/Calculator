#include <string.h>
#include <math.h>
#include "calculation.h"
#include "stack.h"
#include "validate.h"


/*
 * Declaring prototypes.
 */
static int precedence(char operator);
static double calculate(double num1,  double num2, char operator);
static double unaryop(double number, char operator);


void eatSpace(char *exp)
{
	int pos = 0, track = 0;
	while(exp[pos] != '\0') {
		if(exp[pos] != ' ' && exp[pos] != '\t' && exp[pos] != '\n') {
			if(track != pos)
				exp[track] = exp[pos];
			track++;
		}
		pos++;
	}
	exp[track] = '\0';
}

static int precedence(char operator)
{
	switch(operator) {
		case '+':
		case '-':
			return 1;
			break;
		case '/':
		case '*':
			return 2;
			break;
		case '^':
			return 3;
	}
	return -1;
}

static double unaryop(double number, char operator)
{
	switch(operator) {
		case '+':
			return number;
		case '-':
			return -number;
	}
	return 0;
}

static double calculate(double num1,  double num2, char operator)
{
	switch(operator) {
		case '+':
			return (num2 + num1);
		case '-':
			return (num2 - num1);
			
		case '/':
			return (num2 / num1);
			
		case '*':
			return (num2 * num1);
			
		case '^':
			return pow(num2, num1);
	}
	return -1;
}

long double calculation(char *exp)
{
	int pos, trackd;
	char operator, digit[10], unary;
	bool isdigit = false;
	double num1, num2, result;

	Stack *topo, *topd, *trackop;
	Info *info = (Info *)malloc(sizeof(Info));

	/*
	 * Initializing stack.
	 */
	topo = newStack();
	topd = newStack();

	/*
	 * Check for valid expression.
	 */
	if(!isValidExp(exp)) {
		printf("Invalid expression...\n");
		exit(1);
	}

	/*
	 * Initializing variables before use.
	 */
	pos = 0;
	trackd = 0;
	unary = '\0';
	while(exp[pos] != '\0') {
		/*
		 * Collecting and converting to digits.
		 */
		isdigit = false;
		if(isDigit(exp[pos])) {
			isdigit = true;
		}
		if(isdigit) {
			digit[trackd++] = exp[pos];
		} 
		if(exp[pos+1] == '\0')
			isdigit = false;
		if(!isdigit) {
			digit[trackd] = '\0';
			trackd = 0;
			if(strlen(digit) > 0 || exp[pos] == '\0') {
				if(unary != '\0') {
					info->number = unaryop(atof(digit), unary);
					unary = '\0';
				}
				else
					info->number = atof(digit);
				push(&topd, info, false);
			}
		}

		/*
		 * Collecting operators.
		 */
		if(isOperator(exp[pos])) {
			/*
			 * Push parenthesis into stack.
			 */
			if(exp[pos] == '(') {
				info->operator = exp[pos];
				push(&topo, info, true);
				
				pos++;
				continue;
			}
			/*
			 * Unary operator treatment.
			 */
			if(isOperator(exp[pos-1]) && exp[pos-1] != ')' && (exp[pos] != '(' || exp[pos] != ')')) {
				unary = exp[pos];
				pos++;
				continue;
			}

			/*
			 * Push operators and numbers and calculate.
			 */
			if(topo == NULL) {
				if(exp[pos] == '-') {
					unary = exp[pos];
					info->operator = '+';
					push(&topo, info, true);
				} else {
					info->operator = exp[pos];
					push(&topo, info, true);
				}

			} else if(exp[pos] == ')') {
				trackop = topo;
				while(trackop->info->operator != '(') {
					trackop = trackop->next;

					num1 = topd->info->number;
					num2 = topd->next->info->number;
					operator = topo->info->operator;
					result = calculate(num1, num2, operator);
					info->number = result;

					pop(&topd);
					pop(&topd);
					pop(&topo);
					push(&topd, info, false);

					if(trackop ==  NULL)
						break;
				}
				if(topo != NULL)
					pop(&topo);

			} else if(precedence(exp[pos]) >= precedence(topo->info->operator)) {
				if(exp[pos] == '-') {
					unary = exp[pos];
					info->operator = '+';
					push(&topo, info, true);
				} else {
					info->operator = exp[pos];
					push(&topo, info, true);
				}

			} else if(precedence(exp[pos]) < precedence(topo->info->operator)) {
				trackop = topo;
				while(trackop != NULL) {
					if(precedence(exp[pos]) >= precedence(trackop->info->operator) || exp[pos] == ')')
						break;
					trackop = trackop->next;

					num1 = topd->info->number;
					if(topd->next != NULL)
						num2 = topd->next->info->number;
					else
						num2 = 0.0;
					operator = topo->info->operator;
					result = calculate(num1, num2, operator);
					info->number = result;

					pop(&topd);
					pop(&topd);
					pop(&topo);

					/*
					 * Pushing number into stack;
					 */
					push(&topd, info, false);
				}
				/*
				 * Pushing operator into stack;
				 */
				if(exp[pos] == '-') {
					unary = exp[pos];
					info->operator = '+';
					push(&topo, info, true);
				} else {
					info->operator = exp[pos];
					push(&topo, info, true);
				}

			}
		}

		pos++;

		/*
		 * Calculate rest of the stack expressions if exists;
		 */
		if(exp[pos] == '\0') {
			trackop = topo;
			while(trackop != NULL) {
				trackop = trackop->next;

				num1 = topd->info->number;
				if(topd->next != NULL)
					num2 = topd->next->info->number;
				else
					num2 = 0.0;
				operator = topo->info->operator;
				result = calculate(num1, num2, operator);
				info->number = result;

				pop(&topd);
				pop(&topd);
				pop(&topo);
				push(&topd, info, false);
			}
		}
	}

	return result;
}
