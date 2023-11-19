#pragma once

#include <stdbool.h>
#include "errors.h"

typedef struct Stack Stack;

ErrorCode push(Stack** const head, const int value);

int pop(Stack** const head, ErrorCode* errorCode);

void freeStack(Stack** const head);

bool isEmpty(const Stack* const head);
