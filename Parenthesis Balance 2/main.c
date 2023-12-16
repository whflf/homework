#include <stdio.h>
#include <stdlib.h>

#include "include/stack.h"
#include "include/errors.h"
#include "brackets.h"
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

int main(void)
{
    if (!passTests())
    {
        printf(ERROR_FORMAT_STRING, getErrorMessage(testsFailed));
        return testsFailed;
    }

    printf("Enter a string: ");
    char* string = getString();
    if (string == NULL)
    {
        printf(ERROR_FORMAT_STRING, getErrorMessage(outOfMemory));
        return outOfMemory;
    }

    ErrorCode errorCode = ok;
    bool checkResult = parenthesisCheck(string, &errorCode);
    if (errorCode != ok && errorCode != stackIsEmpty)
    {
        printf(ERROR_FORMAT_STRING, getErrorMessage(errorCode));
        free(string);
        return errorCode;
    }

    printf("%s bracket sequence\n", checkResult ? "correct" : "incorrect");

    free(string);
    return ok;
}
