#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

typedef struct QueueElement
{
    int value;
    int priority;
    struct QueueElement* next;
} QueueElement;

struct Queue
{
    struct QueueElement* front;
    struct QueueElement* back;
    size_t size;
};

Queue* createQueue(void)
{
    return (Queue*)calloc(1, sizeof(Queue));
}

static bool isEmpty(const Queue* const queue)
{
    return (queue->front == NULL);
}

ErrorCode enqueue(Queue** const queue, const int value, const int priority)
{
    QueueElement* const newElement = (QueueElement*)calloc(1, sizeof(QueueElement));
    if (newElement == NULL)
    {
        return outOfMemory;
    }

    newElement->value = value;
    newElement->priority = priority;

    if (isEmpty(*queue))
    {
        (*queue)->back = newElement;
        (*queue)->front = newElement;
        return ok;
    }
    else
    {
        if ((*queue)->front->priority > priority)
        {
            newElement->next = (*queue)->front;
            (*queue)->front = newElement;
            return ok;
        }

        QueueElement* tempQueue = (*queue)->front;
        while (tempQueue->next != NULL && tempQueue->next->priority < priority)
        {
            tempQueue = tempQueue->next;
        }

        newElement->next = tempQueue->next;
        tempQueue->next = newElement;
        if (tempQueue == (*queue)->back)
        {
            (*queue)->back = newElement;
        }
    }

    return ok;
}

int dequeue(Queue* const queue)
{
    if (isEmpty(queue))
    {
        return -1;
    }

    QueueElement* tempElement = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL)
    {
        queue->back = NULL;
    }

    const int value = tempElement->value;
    free(tempElement);

    return value;
}

void deleteQueue(Queue** const queue)
{
    while (!isEmpty(*queue))
    {
        dequeue(*queue);
    }

    free(*queue);
    *queue = NULL;
}
