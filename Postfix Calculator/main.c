#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "stack.h"
#include "calculator.h"
#include "tests.h"
#include "errors.h"

char* getString(void)
{
    size_t allocSize = 16, stringSize = 0;

    char* string = malloc(sizeof(char) * allocSize);
    if (string == NULL)
    {
        return NULL;
    }

    char character;
    while ((character = getchar()) != '\n')
    {
        if (stringSize >= allocSize - 1)
        {
            allocSize *= 2;
            string = realloc(string, allocSize * sizeof(char));
            if (string == NULL)
            {
                return NULL;
            }
        }
        string[stringSize] = character;
        ++stringSize;
    }

    string[stringSize] = '\0';

    return string;
}

int main()
{
    if (!passTests())
    {
        printf("~ Tests failed");
        return testsFailed;
    }

    printf("Enter an expression: ");
    char* const expression = getString();
    if (expression == NULL)
    {
        printf("~ Memory allocation has failed");
        return outOfMemory;
    }

    ErrorCode errorCode = ok;
    const int expressionResult = getResult(expression, &errorCode);
    if (errorCode == stackIsEmpty)
    {
        printf("Wrong input. Please enter a valid expression.\n");
        return stackIsEmpty;
    }
    if (errorCode == divisionByZero)
    {
        printf("Division by zero is forbidden. Please enter a valid expression.\n");
        return divisionByZero;
    }

    printf("The result is %d\n", expressionResult);

    free(expression);
    return ok;
}
