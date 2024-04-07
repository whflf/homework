#include <stdio.h>
#include <stdlib.h>

#include "fileParsing.h"

#define DYNAMIC_STRING_MIN_ALLOCATION_SIZE 16

char* getText(const char* const filename, ErrorCode* const error)
{
    FILE* const file = fopen(filename, "r");
    if (file == NULL)
    {
        *error = fileError;
        return NULL;
    }

    size_t allocSize = DYNAMIC_STRING_MIN_ALLOCATION_SIZE, stringSize = 0;

    char* string = (char*)calloc(allocSize, sizeof(char));
    if (string == NULL)
    {
        *error = outOfMemory;
        return NULL;
    }

    char character = '\0';
    char previousCharacter = '\0';
    while ((character = getc(file)) != ' ' && !feof(file))
    {
        if (character == previousCharacter)
        {
            continue;
        }

        if (stringSize >= allocSize - 1)
        {
            allocSize *= 2;
            char* tempString = (char*)realloc(string, allocSize * sizeof(char));
            if (tempString == NULL)
            {
                free(string);
                return NULL;
            }

            string = tempString;
        }
        string[stringSize] = character;
        previousCharacter = character;
        ++stringSize;
    }

    string[stringSize] = '\0';

    return string;
}
