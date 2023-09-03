#include "stack.h"
#include "calculate.h"
#include <stdio.h>

int main() {
	double result = calculate("4/5+(4*4)");
	printf("Result: %lf\n", result);
	return 0;
}
