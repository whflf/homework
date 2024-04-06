#pragma once

#include <stdbool.h>
#include "errors.h"

typedef struct Stack Stack;

typedef char stack_value_t;

ErrorCode push(Stack** const head, const stack_value_t value);

int pop(Stack** const head, ErrorCode* const errorCode);

void freeStack(Stack** const head);

bool isEmpty(const Stack* const head);
