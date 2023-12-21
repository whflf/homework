#include <stdlib.h>
#include <stdio.h>

#include "modules/errors.h"
#include "modules/lexer.h"

#define DYNAMIC_STRING_MIN_ALLOCATION_SIZE 16

char* getString(void)
{
    size_t allocSize = DYNAMIC_STRING_MIN_ALLOCATION_SIZE, stringSize = 0;

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

ErrorCode main(int argc, char* argv[])
{
    if (argc > 1 && strcmp(argv[1], "-tests") == 0)
    {
        return passTests() ? 0 : 1;
    }

    if (!passTests())
    {
        return printErrorMessage(testsFailed);
    }

    printf("> Enter a string to check if it contains a real number: ");
    char* const inputString = getString();
    if (inputString == NULL)
    {
        return printErrorMessage(outOfMemory);
    }

    printf("%s is%s a real number\n", inputString, isNumber(inputString) ? "" : " not");
    
    return ok;
}
