#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"
#include "errors.h"

struct Stack
{
    stack_value_t value;
    struct Stack* previous;
};

ErrorCode push(Stack** const head, const stack_value_t value)
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

stack_value_t top(const Stack* const head, ErrorCode* errorCode)
{
    if (head == NULL)
    {
        *errorCode = stackIsEmpty;
        return stackIsEmpty;
    }

    return head->value;
}

ErrorCode pop(Stack** const head, ErrorCode* errorCode)
{
    if (*head == NULL) 
    {
        *errorCode = stackIsEmpty;
        return stackIsEmpty;
    }

    Stack* temp = *head;
    *head = (*head)->previous;
    free(temp);
    return ok;
}

void freeStack(Stack** const head)
{
    if (head == NULL || *head == NULL)
    {
        return;
    }
    while (head != NULL) 
    {
        ErrorCode errorCode = ok;
        pop(head, &errorCode);
    }
}
