#ifndef POLISHNOTATION_H_
#define POLISHNOTATION_H_

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

#define NMAX 100

enum resultCode { OK, ERROR };

char *removeSpacesFromStr(const char *str, char *parseString);
int processCalculation(const char *inputString, double x, double *result);
int stringToReversePolishNotation(char *str, char *polish);
double calculate(char *str, double x, int *code);

double binaryOperate(char operation, double num1, double num2, int *code);
double unaryOperate(char operation, double num);
int priority(char c);
char isFunction(const char *str, int len, int *i);
int isDigit(char ch);
int isBinaryOperation(char ch);
int isUnaryOperation(char ch);

#endif  //  POLISHNOTATION_H_
