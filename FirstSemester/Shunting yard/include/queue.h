#pragma once

#include <stdbool.h>
#include "errors.h"

typedef struct Queue Queue;

typedef struct QueueElement QueueElement;

typedef char queue_value_t;

Queue* createQueue(void);

bool isEmpty(const Queue* const queue);

void enqueue(Queue* const queue, const queue_value_t value, ErrorCode* const errorCode);

queue_value_t dequeue(Queue* const queue, ErrorCode* const errorCode);

void deleteQueue(Queue** const queue);

size_t queueSize(const Queue* const queue);
