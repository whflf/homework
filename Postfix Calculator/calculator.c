#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "calculator.h"
#include "errors.h"

static int calcExpression(Stack** head, const char sign)
{
    ErrorCode errorCode = ok;
    const int a = pop(head, &errorCode);
    if (errorCode == stackIsEmpty)
    {
        return stackIsEmpty;
    }

    if (isEmpty(*head))
    {
        return stackIsEmpty;
    }

    const int b = pop(head, &errorCode);
    if (errorCode == stackIsEmpty)
    {
        return stackIsEmpty;
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
        if (a == 0)
        {
            return divisionByZero;
        }
        operationResult = b / a;
        break;
    }
    push(head, operationResult);
    return ok;
}

int getResult(char* const string, ErrorCode* errorCode)
{
    Stack* numbers = NULL;

    for (size_t i = 0; string[i] != '\0'; ++i)
    {
        if (string[i] == ' ')
        {
            continue;
        }
        if (string[i] == '+' || string[i] == '-' || string[i] == '*' || string[i] == '/')
        {
            *errorCode = calcExpression(&numbers, string[i]);
            if (*errorCode != ok)
            {
                return *errorCode == stackIsEmpty ? stackIsEmpty : divisionByZero;
            }
        }
        else
        {
            const char strX = string[i];
            const int x = atoi(&strX);
            push(&numbers, x);
        }
    }

    int result = pop(&numbers, errorCode);
    while (!isEmpty(numbers))
    {
        result = pop(&numbers, errorCode);
    }
    freeStack(&numbers);
    return result;
}
