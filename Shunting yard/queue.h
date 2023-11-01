#pragma once

#include <stdbool.h>

typedef struct Queue Queue;

typedef struct QueueElement QueueElement;

typedef char Value;

Queue* createQueue();

void createQueueElement(QueueElement* queueElement, const Value value);

bool isEmpty(Queue* queue);

void enqueue(Queue* queue, const Value value);

int dequeue(Queue* queue);

void deleteQueue(Queue** queue);

int front(Queue* queue);

int back(Queue* queue);

void printQueue(Queue* queue);