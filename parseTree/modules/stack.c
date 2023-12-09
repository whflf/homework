#include <stdlib.h>

#include "stack.h"

struct Stack
{
    StackValue value;
    Stack* previous;
};

ErrorCode push(Stack** const head, const StackValue value)
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

StackValue top(const Stack* const head)
{
    if (head == NULL)
    {
        return (StackValue)0;
    }

    return head->value;
}

void pop(Stack** const head)
{
    if (*head == NULL) 
    {
        return;
    }

    Stack* temp = *head;
    *head = (*head)->previous;
    StackValue value = temp->value;
    free(temp);
}

static void freeStackValues(Stack** const head)
{
    if (head == NULL || *head == NULL)
    {
        return;
    }
    while (head != NULL)
    {
        deleteTree(&((*head)->value));
        *head = (*head)->previous;
    }
}

void freeStack(Stack** const head)
{
    if (head == NULL || *head == NULL)
    {
        return;
    } 
    freeStackValues(head);
    while (head != NULL) 
    {
        pop(head);
    }
}
