#include <stdlib.h>
#include <string.h>

#include "include/stack.h"
#include "include/errors.h"
#include "calculator.h"

static ErrorCode calcExpression(Stack** const head, const char sign)
{
    ErrorCode errorCode = ok, errorCode2 = ok;
    const int a = pop(head, &errorCode);
    const int b = pop(head, &errorCode2);
    if (errorCode == stackIsEmpty || errorCode2 == stackIsEmpty)
    {
        return stackIsEmpty;
    }

    int operationResult = 0;
    switch (sign)
    {
    case '+':
        operationResult = b + a;
        break;
    case '-':
        operationResult = b - a;
        break;
    case '*':
        operationResult = b * a;
        break;
    case '/':
        if (a == 0)
        {
            return divisionByZero;
        }
        operationResult = b / a;
        break;
    }

    return push(head, operationResult);
}

int getResult(const char* const string, ErrorCode* const errorCode)
{
    Stack* numbers = NULL;

    for (size_t i = 0; string[i] != '\0'; ++i)
    {
        if (string[i] == '+' || string[i] == '-' || string[i] == '*' || string[i] == '/')
        {
            ;
            if ((*errorCode = calcExpression(&numbers, string[i])) != ok)
            {
                freeStack(&numbers);
                return 0;
            }
        }
        else if (string[i] != ' ')
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
