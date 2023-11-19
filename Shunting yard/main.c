#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "queue.h"
#include "stack.h"
#include "errors.h"
#include "tests.h"
#include "shuntingYard.h"

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
        printf("~ Tests failed\n");
        return testsFailed;
    }

    printf("Enter an expression: ");
    char* const expression = getString();
    if (expression == NULL)
    {
        printf("~ Memory allocation has failed\n");
        return outOfMemory;
    }

    char* const postfixExpression = getPostfixExpression(expression);
    if (postfixExpression == NULL)
    {
        printf("Wrong input. Please enter a valid expression.\n");
    }
    printf("%s\n", postfixExpression);
    free(expression);
    free(postfixExpression);

    return ok;
}
