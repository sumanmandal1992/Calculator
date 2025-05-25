#include "parseexp.h"
#include <stdio.h>
#include <string.h>
#define max 100


int main()
{
	char exp[max];
	printf("\nEnter expression: ");
	fgets(exp, max, stdin);
	exp[strlen(exp)-1] = '\0';
	print(evaluate(exp));
	printf("\n");
	return 0;
}
