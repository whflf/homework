#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "include/stack.h"
#include "include/errors.h"
#include "calculator.h"
#include "tests.h"

#define ALLOC_SIZE 16

#define ERROR_FORMAT_STRING "[E] %s\n"

char* getString(void)
{
    size_t allocSize = ALLOC_SIZE, stringSize = 0;

    char* string = (char*)malloc(sizeof(char) * allocSize);
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

int main(int argc, char* argv[])
{
    if (argc > 1 && strcmp(argv[1], "run tests") == 0)
    {
        return passTests();
    }

    if (!passTests())
    {
        printf(ERROR_FORMAT_STRING, getErrorMessage(testsFailed));
        return testsFailed;
    }

    printf("Enter an expression: ");
    char* expression = getString();
    if (expression == NULL)
    {
        printf(ERROR_FORMAT_STRING, getErrorMessage(outOfMemory));
        return outOfMemory;
    }

    ErrorCode errorCode;
    const int expressionResult = getResult(expression, &errorCode);
    if (errorCode != ok)
    {
        printf(ERROR_FORMAT_STRING, getErrorMessage(errorCode));
        free(expression);
        return errorCode;
    }

    printf("The result is %d.\n", expressionResult);

    free(expression);
    return ok;
}
