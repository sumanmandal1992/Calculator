#include<stdio.h>
#include "Stack.h"
#include "Calculation.h"
#include "Error.h"

//Verify operand.
int isOperand(char ch)
{
	return ((ch>='0' && ch<='9') || ch=='.');
}

//Define precedence of operator.
int prec(char ch)
{
	switch(ch){
		case '+':
		case '-':
			return 1;

		case '*':
		case '/':
			return 2;
		case '^':
			return 3;
	}
	return -1;
}

//Convert string to double.
double strtoD(char *a)
{
	double s=0,d=1;
	int i=0,j=0;
	while(a[j]!='\0'){
		if(a[j]=='.'){
			while(a[i]!='.'){
				s=s*10+(a[i]-'0');
				i++;
			}
			i++;
			while(a[i]!='\0'){
				d*=10.0;
				s=s+(a[i]-'0')/d;
				i++;
			}
		}
		j++;
	}
	while(a[i]!='\0'){
		s=s*10+(a[i]-'0');
		i++;
	}
	return s;
}

//Calculate length of string.
int len(char *str)
{
	int i=0;
	while(str[i]!='\0')
		i++;
	return i;
}

//Calculation of the expression.
void operation(double *array, int position, char operator)
{
	switch(operator){
		case '+':
			array[(position-1)]=array[(position-1)] + array[position];
			array[position]=0;
			break;
		case '-':
			array[(position-1)]=array[(position-1)] - array[position];
			array[position]=0;
			break;
		case '*':
			array[(position-1)]=array[(position-1)] * array[position];
			array[position]=0;
			break;
		case '/':
			array[(position-1)]=array[(position-1)] / array[position];
			array[position]=0;
			break;
		case '^':
			array[(position-1)]=pow(array[(position-1)], array[position]);
			array[position]=0;
			break;
		default:
			return;
	}
}

//Power function
double pow(double n, double p)
{
	int i;
	double r=1;
	for(i=0; i<p; i++)
		r=r*n;
	return r;
}

//Infix to postfix operation and calculateion.
void calculate(char *exp)
{
	int i=0, j=0, k=0;
	char temp[len(exp)];
	double operand[len(exp)];

	//Create a stack of capacity equal to expression size.
	Stack *stack=createStack(len(exp)/2);
	if(stack==NULL){
		printf("Stack creation failed\n");
		exit(1);
	}
	//Travers expression and calculate.
	while(exp[i]!='\0'){
		//Check if the expression is valid.
		if(!isvalidexp(exp)){
			printf("Systax error or use parenthesis for unary operators. Eg. (-a)\n");
			return;
		}

		//If the scanned character is an operand, add it to operand array.
		if(isOperand(exp[i])){
			temp[j++]=exp[i];
			temp[j]='\0';
			operand[k]=strtoD(temp);
		}

		//If the scanned character is an '(', push it to stack.
		else if(exp[i]=='('){
			push(stack, exp[i]);
		}
		//If the scanned character is an ')', pop and calculate operation until an '(' is encountered.
		else if(exp[i]==')'){
			while(!isEmpty(stack) && peek(stack) != '('){
				operation(operand, k, pop(stack));
				k--;
			}
			operation(operand, k, pop(stack));
		}
		else{ //An operator is encountered.
			while(!isEmpty(stack) && prec(exp[i]) <= prec(peek(stack))){
				operation(operand, k, pop(stack));
				k--;
			}
			push(stack, exp[i]);
			k++;
			j=0;
		}
		i++;
	}
	//pop all the operators from the stack.
	while(!isEmpty(stack)){
		operation(operand, k, pop(stack));
		k--;
	}
	//Delete alocated stack memory when stack is emptied.
	free(stack);
	//Print output.
	printf("%lf\n",operand[0]);
}
