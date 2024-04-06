#pragma once

typedef enum ErrorCode
{
    ok,
    stackIsEmpty,
    outOfMemory,
} ErrorCode;

typedef struct Stack Stack;

Stack* createStack();

ErrorCode push(Stack** head, const int value);

int pop(Stack** head);

void freeStack(Stack** head);

int top(Stack* head, ErrorCode* errorCode);
