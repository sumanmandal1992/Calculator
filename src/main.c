#include "stack.h"
#include "calculate.h"
#include <stdio.h>

int main() {
	char *exp = "4/5+(4*4)";
	double result = calculate(exp);
	printf("Result: %lf\n", result);
	return 0;
}
