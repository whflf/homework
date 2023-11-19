#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "queue.h"
#include "stack.h"
#include "errors.h"
#include "tests.h"

char* getPostfixExpression(char* const expression)
{
    Queue* const outputQueue = createQueue();
    Stack* const stack = NULL;
    ErrorCode errorCode = ok;
    char token = '\0';

    for (size_t i = 0; expression[i] != '\0'; ++i)
    {
        if ('0' <= expression[i] && expression[i] <= '9')
        {
            enqueue(outputQueue, expression[i]);
        }
        else if (expression[i] == '+' || expression[i] == '-')
        {
            token = top(stack, &errorCode);
            if (errorCode == stackIsEmpty && isEmpty(outputQueue))
            {
                return NULL;
            }
            for (; token == '+' || token == '-' || token == '*' || token == '/'; token = top(stack, &errorCode))
            {
                enqueue(outputQueue, token);
                pop(&stack, &errorCode);
            }
            push(&stack, expression[i]);
        }
        else if (expression[i] == '*' || expression[i] == '/')
        {
            token = top(stack, &errorCode);
            if (errorCode == stackIsEmpty && isEmpty(outputQueue))
            {
                return NULL;
            }
            for (; token == '*' || token == '/'; token = top(stack, &errorCode))
            {
                enqueue(outputQueue, token);
                pop(&stack, &errorCode);
            }
            push(&stack, expression[i]);
        }
        else if (expression[i] == '(')
        {
            push(&stack, expression[i]);
        }
        else if (expression[i] == ')')
        {
            token = top(stack, &errorCode);
            if (errorCode == stackIsEmpty && isEmpty(outputQueue))
            {
                return NULL;
            }
            for (; token == '+' || token == '-' || token == '*' || token == '/'; token = top(stack, &errorCode))
            {
                enqueue(outputQueue, token);
                pop(&stack, &errorCode);
            }
            pop(&stack, &errorCode);
        }
    }


    for (token = top(stack, &errorCode); stack != NULL; token = top(stack, &errorCode))
    {
        enqueue(outputQueue, token);
        pop(&stack, &errorCode);
    }

    size_t allocSize = queueSize(outputQueue) + 1;
    char* const outputString = (char*)malloc(allocSize * sizeof(char));
    if (outputString == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; !isEmpty(outputQueue); ++i)
    {
        outputString[i] = dequeue(outputQueue);
    }
    outputString[allocSize - 1] = '\0';

    deleteQueue(&outputQueue);
    return outputString;
}
