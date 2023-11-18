#include "stack.h"
#include <stdlib.h>

struct Stack
{
    int value;
    struct Stack* previous;
};


Stack* createStack()
{
    Stack* stack = calloc(1, sizeof(Stack));
    if (stack == NULL) 
    {
        return NULL;
    }
    return stack;
}

ErrorCode push(Stack** head, const int value)
{
    Stack* next = malloc(sizeof(Stack));
    if (next == NULL) 
    {
        return outOfMemory;
    }
    next->value = value;
    next->previous = *head;
    *head = next;
    return ok;
}

int pop(Stack** head, ErrorCode* errorCode)
{
    if (*head == NULL) 
    {
        *errorCode = stackIsEmpty;
        return stackIsEmpty;
    }

    const int value = (*head)->value;
    Stack* temp = *head;
    *head = (*head)->previous;
    free(temp);
    return value;
}

void freeStack(Stack** head)
{
    if (head == NULL || *head == 0)
    {
        return stackIsEmpty;
    }
    Stack* next = (*head)->previous;
    free(*head);
    while (next != NULL) 
    {
        Stack* temp = next;
        next = next->previous;
        free(temp);
    }
}

int top(Stack* head, ErrorCode* errorCode)
{
    if (head == NULL) 
    {
        *errorCode = stackIsEmpty;
        return 0;
    }

    *errorCode = ok;
    return head->value;
}
