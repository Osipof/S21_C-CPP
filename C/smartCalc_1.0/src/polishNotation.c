#include "polishNotation.h"

#include <stdio.h>

int processCalculation(const char *inputString, double x, double *result) {
  int code = OK;
  *result = 0;
  char parseString[512] = "";
  removeSpacesFromStr(inputString, parseString);
  int len = strlen(parseString);
  char *reversePolishNotation = (char *)malloc(len * 2 * sizeof(char));
  if (len > 255 ||
      stringToReversePolishNotation(parseString, reversePolishNotation)) {
    code = ERROR;
  } else {
    *result = calculate(reversePolishNotation, x, &code);
  }
  if (isnan(*result) || isinf(*result)) {
    code = ERROR;
  }
  free(reversePolishNotation);
  return code;
}

int stringToReversePolishNotation(char *str, char *reversePolishNotation) {
  struct stack *root = init('0');
  int len = strlen(str);
  int count = 0, code = OK;
  int dot_count = 0;
  char symbol;
  int i = 0;
  while (i < len && !code) {
    if ((symbol = isFunction(str, len, &i))) {
      root = push(root, symbol);
      if (symbol == 'm') reversePolishNotation[count++] = ' ';
    } else if (str[i] == 'x' || isDigit(str[i])) {
      if (str[i + 1] == '(' || str[i + 1] == 'x') {
        code = ERROR;
      } else {
        reversePolishNotation[count++] = str[i];
      }
    } else if (str[i] == '.') {
      reversePolishNotation[count++] = ',';
      dot_count++;
      if (dot_count > 1) {
        code = ERROR;
      }
    } else if (str[i] == '(') {
      if (str[i + 1] == ')' ||
          (isBinaryOperation(str[i + 1]) && str[i + 1] != '-') ||
          (str[i + 1] == '-' && str[i + 2] == ')')) {
        code = ERROR;
      } else {
        root = push(root, str[i]);
        if (str[i + 1] == '-' && len - i >= 2) {
          root = push(root, '~');
          i++;
        }
      }
    } else if (str[i] == '-' && i == 0 && str[i + 1] != '\0') {
      root = push(root, '~');
    } else if (isBinaryOperation(str[i])) {
      if (!(isBinaryOperation(str[i + 1]) || str[i + 1] == ')' ||
            str[i + 1] == '\0' || i == 0)) {
        dot_count = 0;
        reversePolishNotation[count++] = ' ';
        if (priority(root->symbol) >= priority(str[i])) {
          reversePolishNotation[count++] = pop(&root);
          reversePolishNotation[count++] = ' ';
          root = push(root, str[i]);
        } else {
          root = push(root, str[i]);
        }
      } else {
        code = ERROR;
      }
    } else if (str[i] == ')') {
      if (str[i + 1] != '\0' && !isBinaryOperation(str[i + 1]) &&
          str[i + 1] != ')') {
        code = ERROR;
      } else {
        while (root->symbol != '(' && !code) {
          if (root->symbol == '0') {
            code = ERROR;
          } else {
            reversePolishNotation[count++] = ' ';
            reversePolishNotation[count++] = pop(&root);
          }
        }
        if (!code) {
          pop(&root);
          if (isUnaryOperation(root->symbol)) {
            reversePolishNotation[count++] = ' ';
            reversePolishNotation[count++] = pop(&root);
          }
        }
      }
    } else if (str[i] != ' ') {
      code = ERROR;
    }
    i++;
  }
  if (root && !code) {
    while (root->symbol != '0') {
      reversePolishNotation[count++] = ' ';
      reversePolishNotation[count++] = pop(&root);
    }
  }
  reversePolishNotation[count] = '\0';
  destroy(root);
  return code;
}

double calculate(char *str, double x, int *code) {
  struct stackNum *root = initNum('0');
  double result;
  for (long unsigned int i = 0; i < strlen(str); i++) {
    if (isDigit(str[i])) {
      char temp[NMAX] = "";
      // находим кол-во символов до пробела
      int kolvo = strcspn(str + i, " ");
      // копируем количество символов до пробела в temp
      strncpy(temp, str + i, kolvo);
      // перевод в double строки temp
      double num = atof(temp);
      // push в стек числа double
      root = pushNum(root, num);
      i += kolvo - 1;
    } else if (str[i] == 'x') {
      root = pushNum(root, x);
    } else if (isBinaryOperation(str[i])) {
      double tempNum1 = popNum(&root);
      double tempNum2 = popNum(&root);
      root = pushNum(root, binaryOperate(str[i], tempNum1, tempNum2, code));
    } else if (str[i] == '~') {
      double tempNum = popNum(&root);
      tempNum = tempNum * (-1);
      root = pushNum(root, tempNum);
    } else if (isUnaryOperation(str[i])) {
      double tempNum = popNum(&root);
      root = pushNum(root, unaryOperate(str[i], tempNum));
    } else if (str[i] != ' ') {
      *code = ERROR;
    }
  }
  result = popNum(&root);
  return result;
}

double binaryOperate(char operation, double num1, double num2, int *code) {
  double result = 0;
  switch (operation) {
    case '+':
      result = num2 + num1;
      break;
    case '-':
      result = num2 - num1;
      break;
    case '*':
      result = num2 * num1;
      break;
    case '/':
      result = num2 / num1;
      break;
    case '^':
      result = pow(num2, num1);
      break;
    case 'm':
      if (num1 - (int)num1 != 0 || num2 - (int)num2 != 0) {
        *code = ERROR;
      } else {
        result = (int)num2 % (int)num1;
      }
      break;
  }
  return result;
}

double unaryOperate(char operation, double num) {
  double result = 0;
  switch (operation) {
    case 's':
      result = sin(num);
      break;
    case 'c':
      result = cos(num);
      break;
    case 't':
      result = tan(num);
      break;
    case 'q':
      result = sqrt(num);
      break;
    case 'l':
      result = log(num);
      break;
    case 'L':
      result = log10(num);
      break;
    case 'S':
      result = asin(num);
      break;
    case 'C':
      result = acos(num);
      break;
    case 'T':
      result = atan(num);
      break;
  }
  return result;
}

char *removeSpacesFromStr(const char *str, char *parseString) {
  int nonSpaceCount = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] != ' ') {
      parseString[nonSpaceCount++] = str[i];
    }
  }
  parseString[nonSpaceCount] = '\0';
  return parseString;
}

int priority(char c) {
  int code = 0;
  switch (c) {
    case '~':
      code = 6;
      break;
    case '^':
      code = 5;
      break;
    case 'm':
      code = 4;
      break;
    case '*':
    case '/':
      code = 3;
      break;
    case '-':
    case '+':
      code = 2;
      break;
    case '(':
      code = 1;
      break;
  }
  return code;
}

char isFunction(const char *str, int len, int *i) {
  char result = '\0';
  if (len - *i >= 3 && str[*i] == 's' && str[*i + 1] == 'i' &&
      str[*i + 2] == 'n' && str[*i + 3] == '(') {
    result = 's';
    *i += 2;
  } else if (len - *i >= 3 && str[*i] == 'c' && str[*i + 1] == 'o' &&
             str[*i + 2] == 's' && str[*i + 3] == '(') {
    result = 'c';
    *i += 2;
  } else if (len - *i >= 3 && str[*i] == 't' && str[*i + 1] == 'a' &&
             str[*i + 2] == 'n' && str[*i + 3] == '(') {
    result = 't';
    *i += 2;
  } else if (len - *i >= 2 && str[*i] == 'l' && str[*i + 1] == 'n' &&
             str[*i + 2] == '(') {
    result = 'l';
    *i += 1;
  } else if (len - *i >= 3 && str[*i] == 'l' && str[*i + 1] == 'o' &&
             str[*i + 2] == 'g' && str[*i + 3] == '(') {
    result = 'L';
    *i += 2;
  } else if (len - *i >= 4 && str[*i] == 's' && str[*i + 1] == 'q' &&
             str[*i + 2] == 'r' && str[*i + 3] == 't' && str[*i + 4] == '(') {
    result = 'q';
    *i += 3;
  } else if (len - *i >= 3 && str[*i] == 'm' && str[*i + 1] == 'o' &&
             str[*i + 2] == 'd') {
    result = 'm';
    *i += 2;
  } else if (len - *i >= 4 && str[*i] == 'a' && str[*i + 1] == 's' &&
             str[*i + 2] == 'i' && str[*i + 3] == 'n' && str[*i + 4] == '(') {
    result = 'S';
    *i += 3;
  } else if (len - *i >= 4 && str[*i] == 'a' && str[*i + 1] == 'c' &&
             str[*i + 2] == 'o' && str[*i + 3] == 's' && str[*i + 4] == '(') {
    result = 'C';
    *i += 3;
  } else if (len - *i >= 4 && str[*i] == 'a' && str[*i + 1] == 't' &&
             str[*i + 2] == 'a' && str[*i + 3] == 'n' && str[*i + 4] == '(') {
    result = 'T';
    *i += 3;
  }
  return result;
}

int isDigit(char ch) { return (ch >= '0' && ch <= '9'); }

int isBinaryOperation(char ch) {
  return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' ||
          ch == 'm');
}

int isUnaryOperation(char ch) {
  return (ch == 's' || ch == 'c' || ch == 't' || ch == 'q' || ch == 'l' ||
          ch == 'L' || ch == 'S' || ch == 'C' || ch == 'T');
}
