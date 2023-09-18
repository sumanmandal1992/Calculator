#include "calculate.h"
#include <stdio.h>

int main() {
	char exp[100];
	printf("Type your expression: ");
	fgets(exp, 100, stdin);
	double result = calculate(exp);
	print(result);
	return 0;
}
