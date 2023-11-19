#pragma once

#include <stdbool.h>

typedef struct Queue Queue;

typedef struct QueueElement QueueElement;

typedef char queue_value_t;

Queue* createQueue(void);

bool isEmpty(Queue* const queue);

void enqueue(Queue* const queue, const queue_value_t value);

int dequeue(Queue* const queue);

void deleteQueue(Queue** const queue);

int front(Queue* const queue);

int back(Queue* const queue);

int queueSize(Queue* const queue);

void printQueue(Queue* const queue);
