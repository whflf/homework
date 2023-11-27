#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "include/queue.h"
#include "include/stack.h"
#include "include/errors.h"
#include "tests.h"

static isOperation(const char token)
{
    return token == '+' || token == '-' || token == '*' || token == '/';
}

char* getPostfixExpression(const char* const expression, ErrorCode* const errorCode)
{
    *errorCode = ok;
    Queue* outputQueue = createQueue();
    if (outputQueue == NULL)
    {
        *errorCode = outOfMemory;
        return NULL;
    }

    Stack* stack = NULL;
    char token = '\0';

    for (size_t i = 0; expression[i] != '\0'; ++i)
    {
        const char curChar = expression[i];

        if (isdigit(curChar))
        {
            enqueue(outputQueue, curChar, errorCode);
            if (*errorCode != ok)
            {
                deleteQueue(&outputQueue);
                return NULL;
            }
        }
        else if (curChar == '+' || curChar == '-')
        {
            token = top(stack, errorCode);
            if (*errorCode == stackIsEmpty && isEmpty(outputQueue))
            {
                deleteQueue(&outputQueue);
                *errorCode = wrongInput;
                return NULL;
            }

            while (isOperation(token))
            {
                enqueue(outputQueue, token, errorCode);
                pop(&stack, errorCode);
                if (*errorCode != ok)
                {
                    deleteQueue(&outputQueue);
                    return NULL;
                }

                token = top(stack, errorCode);
            }

            push(&stack, curChar);
        }
        else if (curChar == '*' || curChar == '/')
        {
            token = top(stack, errorCode);
            if (*errorCode == stackIsEmpty && isEmpty(outputQueue))
            {
                deleteQueue(&outputQueue);
                *errorCode = wrongInput;
                return NULL;
            }

            while (token == '*' || token == '/')
            {
                enqueue(outputQueue, token, errorCode);
                pop(&stack, errorCode);
                if (*errorCode != ok)
                {
                    deleteQueue(&outputQueue);
                    return NULL;
                }

                token = top(stack, errorCode);
            }

            push(&stack, curChar);
        }
        else if (curChar == '(')
        {
            push(&stack, curChar);
        }
        else if (curChar == ')')
        {
            token = top(stack, errorCode);
            if (*errorCode == stackIsEmpty && isEmpty(outputQueue))
            {
                deleteQueue(&outputQueue);
                *errorCode = wrongInput;
                return NULL;
            }

            while (isOperation(token))
            {
                enqueue(outputQueue, token, errorCode);
                pop(&stack, errorCode);
                if (*errorCode != ok)
                {
                    deleteQueue(&outputQueue);
                    return NULL;
                }
                token = top(stack, errorCode);
            }

            pop(&stack, errorCode);
        }
    }

    for (token = top(stack, errorCode); stack != NULL; token = pop(&stack, errorCode))
    {
        enqueue(outputQueue, token, errorCode);
        if (*errorCode != ok)
        {
            deleteQueue(&outputQueue);
            return NULL;
        }
    }

    const size_t allocSize = queueSize(outputQueue) * 2;
    char* outputString = (char*)malloc(allocSize * sizeof(char));
    if (outputString == NULL)
    {
        deleteQueue(&outputQueue);
        return NULL;
    }

    for (size_t i = 0; !isEmpty(outputQueue); i += 2)
    {
        outputString[i] = dequeue(outputQueue, errorCode);
        if (*errorCode != ok)
        {
            return NULL;
        }
        outputString[i + 1] = isEmpty(outputQueue) ? '\0' : ' ';
    }

    deleteQueue(&outputQueue);
    return outputString;
}
