#pragma once

#include <stdbool.h>

typedef enum
{
    ok,
    outOfMemory,
    testsFailed
} ErrorCode;

typedef struct Queue Queue;

Queue* createQueue(void);

ErrorCode enqueue(Queue* const queue, const int value, const int priority);

int dequeue(Queue* const queue);

void deleteQueue(Queue** const queue);
