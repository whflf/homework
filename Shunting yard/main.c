#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "include/queue.h"
#include "include/stack.h"
#include "include/errors.h"
#include "tests.h"
#include "shuntingYard.h"

#define DYNAMIC_STRING_MIN_ALLOCATION_SIZE 16

char* getString(void)
{
    size_t allocSize = DYNAMIC_STRING_MIN_ALLOCATION_SIZE, stringSize = 0;

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

int main(void)
{
    if (!passTests())
    {
        printf(errorMessages[testsFailed]);
        return testsFailed;
    }

    printf("Enter an expression: ");
    char* expression = getString();
    if (expression == NULL)
    {
        printf(errorMessages[outOfMemory]);
        return outOfMemory;
    }

    ErrorCode errorCode;
    char* postfixExpression = getPostfixExpression(expression, &errorCode);
    if (errorCode != ok && errorCode != stackIsEmpty)
    {
        printf(errorMessages[errorCode]);
        free(expression);
        free(postfixExpression);
        return errorCode;
    }

    printf("%s\n", postfixExpression);

    free(expression);
    free(postfixExpression);
    return ok;
}
