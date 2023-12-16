#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/queue.h"
#include "include/stack.h"
#include "include/errors.h"
#include "tests.h"
#include "shuntingYard.h"

#define DYNAMIC_STRING_MIN_ALLOCATION_SIZE 16

#define ERROR_FORMAT_STRING "[E] %s\n"

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

int main(int argc, char* argv[])
{
    if (argc > 1 && strcmp(argv[1], "run tests") == 0)
    {
        return passTests() ? 0 : 1;
    }

    if (!passTests())
    {
        printf(ERROR_FORMAT_STRING, getErrorMessage(testsFailed));
        return testsFailed;
    }

    printf("Enter an expression: ");
    char* const expression = getString();
    if (expression == NULL)
    {
        printf(ERROR_FORMAT_STRING, getErrorMessage(outOfMemory));
        return outOfMemory;
    }

    char* const postfixExpression = getPostfixExpression(expression);
    if (postfixExpression == NULL)
    {
        free(expression);
        return -1;
    }

    printf("%s\n", postfixExpression);

    free(expression);
    free(postfixExpression);
    return ok;
}
