#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"
#include "errors.h"

struct Stack
{
    stack_value_t value;
    Stack* previous;
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

int pop(Stack** const head, ErrorCode* const errorCode)
{
    *errorCode = ok;
    if (*head == NULL) 
    {
        *errorCode = stackIsEmpty;
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
    while (!isEmpty(*head)) 
    {
        ErrorCode errorCode;
        pop(head, &errorCode);
    }
}

bool isEmpty(const Stack* const head)
{
    return head == NULL;
}
