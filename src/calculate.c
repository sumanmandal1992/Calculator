#include "calculate.h"
#include "stack.h"
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int precedence(char op) {
  switch (op) {
  case '^':
    return 20;
  case '/':
  case '*':
    return 19;
  case '+':
  case '-':
    return 18;
  }
  return -1;
}

static bool isoperator(char el) {
  switch (el) {
  case '(':
  case ')':
  case '^':
  case '/':
  case '*':
  case '+':
  case '-':
    return true;
  }
  return false;
}

static double unaryop(double num, char op) {
  double n = 0.0;
  switch (op) {
  case '+':
    n = num;
    break;
  case '-':
    n = -num;
    break;
  }
  return n;
}

double eval(char op, double num1, double num2) {
  double result = 0.0;
  switch (op) {
  case '+':
    result = num1 + num2;
    break;
  case '-':
    result = num1 - num2;
    break;
  case '*':
    result = num1 * num2;
    break;
  case '/':
    result = num1 / num2;
    break;
  case '^':
    result = pow(num1, num2);
    break;
  default:
    exit(0);
  }
  return result;
}

static void error(char *expm) {
  printf("Invalid expression...\n");
  printf("Check the expression and retype it...\n");
  while (popop() != '\0')
    ;
  while (popnum() != -0.0)
    ;
  free(expm);
  exit(1);
}

double calculate(char *exp) {
  char *expm = NULL;

  if (strlen(exp) <= 0) {
    printf("No expression given...\n");
    exit(0);
  }

  if (exp[strlen(exp) - 1] == '\n')
    exp[strlen(exp) - 1] = '\0';

  expm = (char*)malloc(sizeof(char) * strlen(exp) + 2);
  expm[0] = '(';
  expm[1] = '\0';
  strcat(expm, exp);
  expm = (char*)realloc(expm, sizeof(char) * strlen(expm) + 2);
  strcat(expm, ")");

  int i = 0, j = 0;
  char ch, curop, num[20], uniop = '\0';
  while ((ch = expm[i++]) != '\0') {
    if (ch == ' ')
      continue;
    else if (isoperator(ch)) {
      if (ch == '(') {
        if (isoperator(expm[i]) && (expm[i] == '+' || expm[i] == '-'))
          uniop = expm[i++];
        pushop(ch);
      } else if (ch == ')')
        while ((curop = popop()) != '(') {
          double ev = eval(curop, popnum(), popnum());

          // Checking for stack underflow
          if (ev == -0.0)
            error(expm);
          pushnum(ev);
        }
      else if (precedence(ch) > precedence(peepop()))
        pushop(ch);
      else if (precedence(ch) <= precedence(peepop())) {
        while (precedence(ch) <= precedence(peepop()))
          pushnum(eval(popop(), popnum(), popnum()));
        pushop(ch);
      }
      if (isoperator(expm[i]) && (expm[i] == '+' || expm[i] == '-'))
        uniop = expm[i++];
    } else if (isdigit(ch)) {
      j = 0;
      if (i >= 3 && isoperator(expm[i - 2]) && isoperator(expm[i - 3]) &&
          (expm[i - 2] != '+' && expm[i - 2] != '-' && expm[i - 2] != '(' &&
           expm[i - 3] != ')'))
        error(expm);
      num[j++] = ch;
      while (!isoperator(ch = expm[i++]))
        num[j++] = ch;
      i--;
      num[j] = '\0';
      if (uniop != '\0')
        pushnum(unaryop(atof(num), uniop));
      else
        pushnum(atof(num));
    } else if (isalpha(ch))
      error(expm);
  } // end while

  const double res = popnum();
  // Checking for stack underflow
  if (popop() != '\0' || popnum() != -0.0) {
    error(expm);
  }
  free(expm);

  return res;
}

void print(double result) {
  if (round(result * 10000000000) / 10000000000 < result ||
      round(result * 10000000000) / 10000000000 > result)
    printf("Result: %.10lf\n", result);
  else if (round(result * 1000000000) / 1000000000 < result ||
           round(result * 1000000000) / 1000000000 > result)
    printf("Result: %.9lf\n", result);
  else if (round(result * 10000000) / 10000000 < result ||
           round(result * 10000000) / 10000000 > result)
    printf("Result: %.8lf\n", result);
  else if (round(result * 1000000) / 1000000 < result ||
           round(result * 1000000) / 1000000 > result)
    printf("Result: %.7lf\n", result);
  else if (round(result * 100000) / 100000 < result ||
           round(result * 100000) / 100000 > result)
    printf("Result: %lf\n", result);
  else if (round(result * 10000) / 10000 < result ||
           round(result * 10000) / 10000 > result)
    printf("Result: %.5lf\n", result);
  else if (round(result * 1000) / 1000 < result ||
           round(result * 1000) / 1000 > result)
    printf("Result: %.4lf\n", result);
  else if (round(result * 100) / 100 < result ||
           round(result * 100) / 100 > result)
    printf("Result: %.3lf\n", result);
  else if (round(result * 10) / 10 < result || round(result * 10) / 10 > result)
    printf("Result: %.2lf\n", result);
  else if (round(result) > result || round(result) < result)
    printf("Result: %.1lf\n", result);
  else
    printf("Result: %.0lf\n", result);
}
