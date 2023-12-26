#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileParsing.h"

static char* getString(FILE* const file)
{
    size_t allocSize = DYNAMIC_STRING_MIN_ALLOCATION_SIZE, stringSize = 0;

    char* string = calloc(allocSize, sizeof(char));
    if (string == NULL)
    {
        return NULL;
    }

    char character;
    while ((character = getc(file)) != ' ' && !feof(file))
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

HashTable* getFrequencyTableFromFile(const char* const filename, ErrorCode* const error)
{
    FILE* const file = fopen(filename, "r");
    if (file == NULL)
    {
        *error = fileError;
        return NULL;
    }

    HashTable* frequencyTable = createHashTable(TABLE_INITIAL_SIZE);
    while (!feof(file))
    {
        char* const key = getString(file);
        if (key[0] == '\0') break;
        if (key == NULL || addEntry(&frequencyTable, key) == outOfMemory)
        {
            fclose(file);
            deleteHashTable(&frequencyTable);
            *error = outOfMemory;
            return NULL;
        }

        free(key);
    }

    fclose(file);
    return frequencyTable;
}
