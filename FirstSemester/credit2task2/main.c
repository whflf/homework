#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

bool firstTest(void)
{
    Queue* const queue = createQueue();

    const int values[] = { 3, 9, 6, 8, 1, 5 };
    ErrorCode error = ok;
    for (size_t i = 0; i < 6; ++i)
    {
        error = enqueue(queue, values[i]);
        if (error)
        {
            printf("Couldn't allocate memory.\n");
            deleteQueue(&queue);
            return false;
        }
    }

    for (size_t i = 0; i < 6; ++i)
    {
        if (dequeue(queue, &error) != values[i])
        {
            return false;
        }
    }

    dequeue(queue, &error);
    deleteQueue(&queue);
    return error == emptyQueue;
}

bool secondTest(void)
{
    Queue* const queue = createQueue();
    ErrorCode error = ok;
    dequeue(queue, &error);
    deleteQueue(&queue);
    return error == emptyQueue;
}

ErrorCode main(void)
{
    if (!firstTest() || !secondTest())
    {
        printf("Tests failed.\n");
        return testsFailed;
    }

    printf("OK\n");
    return ok;
}
