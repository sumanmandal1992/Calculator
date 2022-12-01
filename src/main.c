#include "stack.h"
#include "calculation.h"
#define MAX 100

int main()
{
	char exp[MAX];
	double result;
	printf("Enter expression:\n");
	fgets(exp, MAX, stdin);
	eatSpace(exp);
	result = calculation(exp);
	if((int)result == result)
		printf("Result is: %.0lf\n\n", result);
	else
		printf("Result is: %lf\n\n", result);
	return 0;
}
