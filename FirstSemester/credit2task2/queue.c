#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "stack.h"

typedef struct Queue
{
    Stack* firstStack;
    Stack* secondStack;
} Queue;

Queue* createQueue(void)
{
    return (Queue*)calloc(1, sizeof(Queue));
}

bool queueIsEmpty(const Queue* const queue)
{
    return stackIsEmpty(queue->firstStack) && stackIsEmpty(queue->secondStack);
}

ErrorCode enqueue(Queue* const queue, const int value)
{
    return push(&queue->firstStack, value);
}

static ErrorCode transferValues(Stack** const firstStack, Stack** const secondStack)
{
    ErrorCode error = ok;
    do
    {
        const int value = pop(firstStack, &error);
        error = push(secondStack, value);

        if (error != ok)
        {
            break;
        }
    } while (!stackIsEmpty(*firstStack));

    return error;
}

int dequeue(Queue* const queue, ErrorCode* const error)
{
    if (queueIsEmpty(queue))
    {
        *error = emptyQueue;
        return 0;
    }

    if (stackIsEmpty(queue->secondStack))
    {
        *error = transferValues(&queue->firstStack, &queue->secondStack);
    }

    if (*error != outOfMemory)
    {
        return pop(&queue->secondStack, error);
    }
    return 0;
}

void deleteQueue(Queue** const queue)
{
    if (!queueIsEmpty(*queue))
    {
        freeStack(&(*queue)->firstStack);
        freeStack(&(*queue)->secondStack);
    }
    free(*queue);
    *queue = NULL;
}
