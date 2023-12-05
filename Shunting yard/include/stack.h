#pragma once

#include <stdbool.h>
#include "errors.h"

typedef struct Stack Stack;

typedef char stack_value_t;

ErrorCode push(Stack** const head, const stack_value_t value);

stack_value_t pop(Stack** const head, ErrorCode* const errorCode);

stack_value_t top(const Stack* const head, ErrorCode* const errorCode);

void freeStack(Stack** const head);
