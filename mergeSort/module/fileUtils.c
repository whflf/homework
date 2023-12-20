#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "list.h"
#include "fileUtils.h"

#define INPUT_FILE_ENTRY_DELIMITER " - "

ErrorCode readFile(const char* const filename, char** const content, size_t* const fileSize)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return printErrorMessage(fileError, "File error occurred while executing fopen() in readFile()");
    }

    fseek(file, 0, SEEK_END);

    const long ftellResult = ftell(file);
    if (ftellResult == -1L)
    {
        fclose(file);
        return printErrorMessage(fileError, "File error occurred while executing ftell() in readFile()");
    }

    *fileSize = (size_t)ftellResult;

    fseek(file, 0, SEEK_SET);

    *content = calloc(*fileSize + 1, sizeof(char));
    if (*content == NULL)
    {
        fclose(file);
        return printErrorMessage(outOfMemory, "While allocating memory for content in readFile()");
    }

    fread(*content, sizeof(char), *fileSize, file);

    fclose(file);
    return ok;
}

int deserializeBookContent(const char* const content, List** book)
{
    const char* position = content;
    ErrorCode error = ok;
    while (*position != '\0')
    {
        const char* const positionPre = position;

        const char* entryEnd = strchr(positionPre, '\n');
        if (entryEnd == NULL)
        {
            entryEnd = strchr(positionPre, '\0');
            position = entryEnd;
        }
        else
        {
            position = entryEnd + 1;
        }

        const char* const delimiter = strstr(positionPre, INPUT_FILE_ENTRY_DELIMITER);

        const size_t nameLength = delimiter - positionPre;
        const size_t phoneLength = entryEnd - delimiter - 3;

        char* const name = calloc(nameLength + 1, sizeof(char));
        char* const phone = calloc(phoneLength + 1, sizeof(char));
        if (name == NULL || phone == NULL)
        {
            free(name);
            free(phone);
            return printErrorMessage(
                outOfMemory,
                "While allocating memory for name/phone in deserializeBookContent()"
            );
        }

        memcpy(name, positionPre, nameLength);
        memcpy(phone, positionPre + nameLength + 3, phoneLength);
        if ((error = append(book, name, phone)) != ok)
        {
            free(name);
            free(phone);
            return error;
        }
    }

    convertCircularListToNonCircular(*book);
    return ok;
}
