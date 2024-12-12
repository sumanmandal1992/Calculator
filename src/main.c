#include "parseexp.h"
#include <stdio.h>
#include <string.h>
#define max 100


int main()
{
	char exp[max];
	printf("Enter infix expression: ");
	fgets(exp, max, stdin);
	exp[strlen(exp)-1] = '\0';
	print(evaluate(exp));
	return 0;
}
