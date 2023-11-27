#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"
#include "errors.h"

typedef struct QueueElement
{
    queue_value_t value;
    struct QueueElement* next;
} QueueElement;

typedef struct Queue
{
    struct QueueElement* front;
    struct QueueElement* back;
    size_t size;
} Queue;

Queue* createQueue(void)
{
    return calloc(1, sizeof(Queue));
}

static void createQueueElement(QueueElement* const queueElement, const queue_value_t value)
{
    queueElement->next = NULL;
    queueElement->value = value;
}

bool isEmpty(const Queue* const queue)
{
    return (queue->front == NULL);
}

void enqueue(Queue* const queue, const queue_value_t value)
{
    QueueElement* newElement = (QueueElement*)malloc(sizeof(QueueElement));
    createQueueElement(newElement, value);

    if (queue->back == NULL && queue->front == NULL)
    {
        queue->back = newElement;
        queue->front = newElement;
    }
    else
    {
        queue->back->next = newElement;
        queue->back = newElement;
    }
    ++queue->size;
}

queue_value_t dequeue(Queue* const queue, ErrorCode* const errorCode)
{
    *errorCode = ok;
    if (isEmpty(queue))
    {
        *errorCode = queueIsEmpty;
        return 0;
    }

    QueueElement* tmpElement = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) 
    {
        queue->back = NULL;
    }
    queue_value_t value = tmpElement->value;
    free(tmpElement);
    --queue->size;

    return value;
}

void deleteQueue(Queue** const queue)
{
    while (!isEmpty(*queue))
    {
        ErrorCode errorCode;
        dequeue(*queue, &errorCode);
    }
    free(*queue);
    *queue = NULL;
}

size_t queueSize(const Queue* const queue)
{
    return queue->size;
}

void printQueue(const Queue* const queue)
{
    QueueElement* tmpElement = queue->front;
    while (tmpElement)
    {
        printf("%c ", tmpElement->value);
        tmpElement = tmpElement->next;
    }
}
