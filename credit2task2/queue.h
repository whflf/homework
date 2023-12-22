#pragma once

#include <stdbool.h>
#include "errors.h"

typedef struct Queue Queue;

// initializes new queue
Queue* createQueue(void);

// checks if the queue contains any elements
bool queueIsEmpty(const Queue* const queue);

// adds new value to the queue
ErrorCode enqueue(Queue* const queue, const int value);

// deletes a value from the queue and returns it
int dequeue(Queue* const queue, ErrorCode* const error);

// frees all memory used by the queue
void deleteQueue(Queue** const queue);
