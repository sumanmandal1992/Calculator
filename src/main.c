#include "stack.h"
#include "calculation.h"
#define MAX 100

int main()
{
	char exp[MAX];
	long double result;
	printf("Enter expression:\n");
	fgets(exp, MAX, stdin);
	eatSpace(exp);
	result = calculation(exp);
	if((int)result == result)
		printf("Result: %.0Lf\n\n", result);
	else
		printf("Result: %Lf\n\n", result);
	return 0;
}
