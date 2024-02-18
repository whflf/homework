#pragma once

#include <stdbool.h>
#include "errors.h"

typedef struct Stack Stack;

// checks if the stack contains any elements
bool stackIsEmpty(const Stack* const head);

// add new value to the stack
ErrorCode push(Stack** const head, const int value);

// delete a value from the stack and returns it
int pop(Stack** const head, ErrorCode* errorCode);

// frees all memory used by the stack
void freeStack(Stack** const head);
