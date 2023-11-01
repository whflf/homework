#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "queue.h"
#include "stack.h"

#define LENGTH 51
#define OK 0
#define TESTS_FAILED 1
#define OUT_OF_MEMORY 2

Queue* const getPostfixExpression(char* const expression)
{
    size_t i = 0;
    Queue* const outputQueue = createQueue();
    Stack* const stack = createStack();
    int errorCode = ok;

    while (expression[i] != '\n') 
    {
        if (expression[i] == '0' || expression[i] == '1' || expression[i] == '2' || expression[i] == '3' || \
            expression[i] == '4' || expression[i] == '5' || expression[i] == '6' || expression[i] == '7' || \
            expression[i] == '8' || expression[i] == '9') 
        {
            enqueue(outputQueue, expression[i]);
        }
        else if (expression[i] == '+' || expression[i] == '-') 
        {
            while (top(stack, &errorCode) == '+' || top(stack, &errorCode) == '-' || top(stack, &errorCode) == '*' || \
                top(stack, &errorCode) == '/')
            {
                enqueue(outputQueue, pop(&stack));
            }
            push(&stack, expression[i]);
        }
        else if (expression[i] == '*' || expression[i] == '/')
        {
            while (top(stack, &errorCode) == '*' || top(stack, &errorCode) == '/')
            {
                enqueue(outputQueue, pop(&stack));
            }
            push(&stack, expression[i]);
        }
        else if (expression[i] == '(') 
        {
            push(&stack, expression[i]);
        }
        else if (expression[i] == ')') 
        {
            while (top(stack, &errorCode) == '+' || top(stack, &errorCode) == '-' || top(stack, &errorCode) == '*' ||\
                top(stack, &errorCode) == '/')
            {
                enqueue(outputQueue, pop(&stack));
            }
            pop(&stack);
        }
        ++i;
    }

    while (top(stack, &errorCode) != '\0') 
    {
        enqueue(outputQueue, pop(&stack));
    }

    freeStack(&stack);
    return outputQueue;
}

bool test1() 
{
    const int expressionLength = 11;

    char* const infixExpression = "(5*6-9*3)+8/4\n";
    char* const postfixExpression = "56*93*-84/+";
    Queue* const queueExpression = getPostfixExpression(infixExpression);
    char* const compareExpression = (char*)malloc(expressionLength * sizeof(char));
    if (compareExpression == NULL) 
    {
        return 0;
    }

    size_t i = 0;
    while (!isEmpty(queueExpression))
    {
        compareExpression[i] = dequeue(queueExpression);
        ++i;
    }

    return memcmp(postfixExpression, compareExpression, expressionLength) == 0;
}

bool test2()
{
    const int expressionLength = 11;

    char* const infixExpression = "9/(6-7)*2*(1+1)\n";
    char* const postfixExpression = "967-/2*11+*";
    Queue* const queueExpression = getPostfixExpression(infixExpression);
    char* const compareExpression = (char*)malloc(expressionLength * sizeof(char));
    if (compareExpression == NULL)
    {
        return 0;
    }

    size_t i = 0;
    while (!isEmpty(queueExpression))
    {
        compareExpression[i] = dequeue(queueExpression);
        ++i;
    }

    return memcmp(postfixExpression, compareExpression, expressionLength) == 0;
}

int main()
{
    if (!test1() || !test2()) 
    {
        printf("~ Tests have failed");
        return TESTS_FAILED;
    }
    char* const expression = (char*)malloc(LENGTH * sizeof(char));
    if (expression == NULL) 
    {
        printf("~ Memory allocation has failed");
        return OUT_OF_MEMORY;
    }
    printf("Enter an expression: ");
    fgets(expression, LENGTH, stdin);

    Queue* const postfixExpression = getPostfixExpression(expression);
    printQueue(postfixExpression);
    deleteQueue(&postfixExpression);

    return OK;
}
