#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "queue.h"

bool test1(void)
{
    Queue* priorityQueue = createQueue();

    ErrorCode errors[5] = { enqueue(&priorityQueue, 1, 3),
    enqueue(&priorityQueue, 2, 1),
    enqueue(&priorityQueue, 3, 2),
    enqueue(&priorityQueue, 4, 5),
    enqueue(&priorityQueue, 5, 4) };

    for (size_t i = 0; i < 5; ++i)
    {
        if (errors[i] != ok)
        {
            deleteQueue(&priorityQueue);
            return false;
        }
    }

    int* comparativeArray[] = {2, 3, 1, 5, 4};

    for (size_t i = 0; i < 5; ++i)
    {
        if (dequeue(priorityQueue) != comparativeArray[i])
        {
            deleteQueue(&priorityQueue);
            return false;
        }
    }

    deleteQueue(&priorityQueue);
    return true;
}

bool test2(void)
{
    Queue* priorityQueue = createQueue();

    return dequeue(priorityQueue) == -1;
}

int main(void)
{
    if (!test1() || !test2())
    {
        printf("~Tests failed.\n");
        return testsFailed;
    }

    printf("OK\n");
    return ok;
}
