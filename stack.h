#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
typedef struct stack Stack;
struct stack {
    char body;
    Stack* next;
};

Stack* init(const char in);
Stack* push(Stack* root, const char in);
int pop(Stack** root);
void destroy(Stack* root);
void print(Stack* root);

#endif
