#include <stdlib.h>
#include <string.h>

#include "stack.h"

#define OK 0
#define TESTS_FAILED 1
#define OUT_OF_MEMORY 2

static void calcExpression(Stack** head, const char sign)
{
    if (*head == NULL)
    {
        push(head, 0);
        return;
    }

    const int a = pop(head);
    if (*head == NULL)
    {
        push(head, 0);
        return;
    }

    const int b = pop(head);
    if (*head == NULL)
    {
        push(head, 0);
        return;
    }

    int operationResult = 0;
    switch (sign)
    {
    case '+':
        operationResult = a + b;
        break;
    case '-':
        operationResult = b - a;
        break;
    case '*':
        operationResult = a * b;
        break;
    case '/':
        operationResult = b / a;
        break;
    }
    push(head, operationResult);
}

int getResult(char* token)
{
    Stack* numbers = createStack();

    char const delimiter = ' ';
    char* context = NULL;
    size_t i = 0;
    while (token != NULL)
    {
        if (*token == '+' || *token == '-' || *token == '*' || *token == '/')
        {
            calcExpression(&numbers, *token);
        }
        else
        {
            const int x = atoi(token);
            push(&numbers, x);
        }
        token = strtok_s(NULL, &delimiter, &context);
    }

    ErrorCode errorCode = ok;
    const int result = top(numbers, &errorCode);
    freeStack(&numbers);
    return result;
}
