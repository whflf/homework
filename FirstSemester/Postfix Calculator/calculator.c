#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    default:
        return badInput;
    }

    return push(head, operationResult);
}

int getResult(const char* const string, ErrorCode* const errorCode)
{
    Stack* numbers = NULL;

    for (size_t i = 0; string[i] != '\0'; ++i)
    {
        const char currChar = string[i];
        if (isdigit(currChar))
        {
            const char strX = currChar;
            const int x = atoi(&strX);
            push(&numbers, x);
        }
        else if (currChar != ' ')
        {
            if ((*errorCode = calcExpression(&numbers, currChar)) != ok)
            {
                freeStack(&numbers);
                return 0;
            }
        }
    }

    int result = pop(&numbers, errorCode);
    if (!isEmpty(numbers))
    {
        return badInput;
    }

    freeStack(&numbers);
    return result;
}
