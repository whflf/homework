#include "Queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct QueueElement
{
    Value value;
    struct QueueElement* next;
} QueueElement;

typedef struct Queue
{
    struct QueueElement* front;
    struct QueueElement* back;
} Queue;

Queue* createQueue()
{
    Queue* queue = calloc(1, sizeof(Queue));
    if (queue == NULL) 
    {
        return 1;
    }
    return queue;
}

void createQueueElement(QueueElement* queueElement, const Value value)
{
    queueElement->next = 0;
    queueElement->value = value;
}

bool isEmpty(Queue* queue)
{
    return (queue->front == NULL);
}

void enqueue(Queue* queue, const Value value)
{
    QueueElement* newElement = malloc(sizeof(QueueElement));
    createQueueElement(newElement, value);

    if ((queue->back == NULL) && (queue->front == NULL))
    {
        queue->back = newElement;
        queue->front = newElement;
    }
    else
    {
        queue->back->next = newElement;
        queue->back = newElement;
    }
}

int dequeue(Queue* queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty!");
        return EXIT_FAILURE;
    }
    QueueElement* tmpElement = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) 
    {
        queue->back = NULL;
    }
    Value value = tmpElement->value;
    free(tmpElement);

    return value;
}

void deleteQueue(Queue** queue)
{
    while (!isEmpty(*queue))
    {
        dequeue(*queue);
    }
    free(*queue);
    *queue = NULL;
}

int front(Queue* queue)
{
    return queue->front->value;
}

int back(Queue* queue)
{
    return queue->back->value;
}

void printQueue(Queue* queue)
{
    QueueElement* tmpElement = queue->front;
    while (tmpElement)
    {
        printf("%c ", tmpElement->value);
        tmpElement = tmpElement->next;
    }
}