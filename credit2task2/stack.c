#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"

struct Stack
{
    int value;
    struct Stack* previous;
};

bool stackIsEmpty(const Stack* const head)
{
    return head == NULL;
}

ErrorCode push(Stack** const head, const int value)
{
    Stack* next = (Stack*)malloc(sizeof(Stack));
    if (next == NULL)
    {
        return outOfMemory;
    }
    next->value = value;
    next->previous = *head;
    *head = next;
    return ok;
}

int pop(Stack** const head, ErrorCode* const errorCode)
{
    if (stackIsEmpty(*head))
    {
        *errorCode = emptyStack;
        return 0;
    }

    const int value = (*head)->value;
    Stack* temp = *head;
    *head = (*head)->previous;
    free(temp);
    return value;
}

void freeStack(Stack** const head)
{
    if (head == NULL || *head == NULL)
    {
        return;
    }
    while (!stackIsEmpty(*head))
    {
        ErrorCode errorCode = ok;
        pop(head, &errorCode);
    }
}
