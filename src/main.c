#include "calculate.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  double result = 0.0;
  if(argc > 1) result = calculate(argv[1]);
  else {
    char exp[100];
    printf("Type your expression: ");
    fgets(exp, 100, stdin);
    result = calculate(exp);
  }
  print(result);
  return 0;
}
