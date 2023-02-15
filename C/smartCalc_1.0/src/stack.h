#ifndef STACK_H_
#define STACK_H_

struct stack {
  char symbol;
  struct stack *next;
};

struct stackNum {
  double num;
  struct stackNum *next;
};

char pop(struct stack **root);
struct stack *init(char symbol);
struct stack *push(struct stack *root, char symbol);
void destroy(struct stack *root);

double popNum(struct stackNum **root);
struct stackNum *initNum(double number);
struct stackNum *pushNum(struct stackNum *root, double number);

#endif  // STACK_H_
