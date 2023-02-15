#include "stack.h"

#include <stdlib.h>

struct stack *init(char symbol) {
  struct stack *header = (struct stack *)malloc(sizeof(struct stack));
  header->symbol = symbol;
  header->next = NULL;
  return header;
}

struct stack *push(struct stack *root, char symbol) {
  struct stack *new = (struct stack *)malloc(sizeof(struct stack));
  new->next = root;
  new->symbol = symbol;
  root = new;
  return root;
}

void destroy(struct stack *root) {
  struct stack *temp = root;
  while (root != NULL) {
    temp = temp->next;
    free(root);
    root = temp;
  }
}

char pop(struct stack **root) {
  struct stack *ptr;
  char c;
  if (*root == NULL) {
    return '\0';
  }
  ptr = *root;
  c = ptr->symbol;
  *root = ptr->next;
  free(ptr);
  return c;
}

struct stackNum *initNum(double number) {
  struct stackNum *header = (struct stackNum *)malloc(sizeof(struct stackNum));
  header->num = number;
  header->next = NULL;
  return header;
}

struct stackNum *pushNum(struct stackNum *root, double number) {
  struct stackNum *new = (struct stackNum *)malloc(sizeof(struct stackNum));
  new->next = root;
  new->num = number;
  root = new;
  return root;
}

double popNum(struct stackNum **root) {
  struct stackNum *ptr;
  double n;
  if (*root == NULL) {
    return '\0';
  }
  ptr = *root;
  n = ptr->num;
  *root = ptr->next;
  free(ptr);
  return n;
}
