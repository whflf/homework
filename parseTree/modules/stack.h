#pragma once

#include "errors.h"
#include "tree.h"

typedef struct Stack Stack;

typedef Node* StackValue;

ErrorCode push(Stack** const head, const StackValue value);

void pop(Stack** const head);

StackValue top(const Stack* const head);

void freeStack(Stack** const head);
