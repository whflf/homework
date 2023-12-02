#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <ctype.h>

#include "include/queue.h"
#include "include/stack.h"
#include "include/errors.h"
#include "tests.h"

static bool isOperation(const char token)
{
    return token == '+' || token == '-' || token == '*' || token == '/';
}

static char getPriority(const char sign)
{
    return sign == '+' || sign == '-' ? 0 : 1;
}

static void destroyQueueAndStack(Queue** const queue, Stack** const stack)
{
    deleteQueue(queue);
    freeStack(stack);
}

char* getPostfixExpression(const char* const expression)
{
    Queue* outputQueue = createQueue();
    if (outputQueue == NULL)
    {
        return NULL;
    }

    ErrorCode errorCode = ok;

    Stack* stack = NULL;
    char token = '\0';

    for (size_t i = 0; expression[i] != '\0'; ++i)
    {
        const char curChar = expression[i];

        if (isdigit(curChar))
        {
            enqueue(outputQueue, curChar, &errorCode);
            if (errorCode != ok)
            {
                destroyQueueAndStack(&outputQueue, &stack);
                return NULL;
            }
        }
        else if (curChar == '+' || curChar == '-' || curChar == '*' || curChar == '/' || curChar == ')')
        {
            token = pop(&stack, &errorCode);
            if (errorCode == stackIsEmpty && isEmpty(outputQueue))
            {
                destroyQueueAndStack(&outputQueue, &stack);
                return NULL;
            }

            while (isOperation(token) && (curChar == ')' || getPriority(curChar) <= getPriority(token)))
            {
                enqueue(outputQueue, token, &errorCode);
                if (errorCode != ok)
                {
                    destroyQueueAndStack(&outputQueue, &stack);
                    return NULL;
                }

                token = pop(&stack, &errorCode);
            }

            curChar == ')' ? pop(&stack, &errorCode) : push(&stack, curChar);
        }
        else if (curChar == '(')
        {
            push(&stack, curChar);
        }
    }

    if (isEmpty(outputQueue))
    {
        destroyQueueAndStack(&outputQueue, &stack);
        return NULL;
    }

    for (token = top(stack, &errorCode); stack != NULL; token = pop(&stack, &errorCode))
    {
        enqueue(outputQueue, token, &errorCode);
        if (errorCode != ok)
        {
            destroyQueueAndStack(&outputQueue, &stack);
            return NULL;
        }
    }

    const size_t allocSize = queueSize(outputQueue) * 2;
    char* outputString = (char*)calloc(allocSize, sizeof(char));
    if (outputString == NULL)
    {
        destroyQueueAndStack(&outputQueue, &stack);
        return NULL;
    }

    for (size_t i = 0; !isEmpty(outputQueue); i += 2)
    {
        outputString[i] = dequeue(outputQueue, &errorCode);
        if (errorCode != ok)
        {
            destroyQueueAndStack(&outputQueue, &stack);
            return NULL;
        }
        outputString[i + 1] = isEmpty(outputQueue) ? '\0' : ' ';
    }

    destroyQueueAndStack(&outputQueue, &stack);
    return outputString;
}

