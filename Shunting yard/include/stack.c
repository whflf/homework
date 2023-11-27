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
    *errorCode = ok;
    if (head == NULL)
    {
        *errorCode = stackIsEmpty;
        return (stack_value_t)0;
    }

    return head->value;
}

stack_value_t pop(Stack** const head, ErrorCode* errorCode)
{
    *errorCode = ok;
    if (*head == NULL) 
    {
        *errorCode = stackIsEmpty;
        return (stack_value_t)0;
    }

    Stack* temp = *head;
    *head = (*head)->previous;
    stack_value_t value = temp->value;
    free(temp);
    return value;
}

void freeStack(Stack** const head)
{
    if (head == NULL || *head == NULL)
    {
        return;
    }
    while (head != NULL) 
    {
        ErrorCode errorCode;
        pop(head, &errorCode);
    }
}
