#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "phoneBook.h"
#include "errors.h"
#include "fileParsing.h"

ErrorCode readFile(FILE* const file, char** const content, size_t* const fileSize)
{
    fseek(file, 0, SEEK_END);

    const long ftellResult = ftell(file);
    if (ftellResult == -1L)
    {
        return printErrorMessage(fileError, "ftell() failed in readFile()", true);
    }

    *fileSize = (size_t)ftellResult;

    fseek(file, 0, SEEK_SET);

    *content = (char*)calloc(*fileSize + 1, sizeof(char));
    if (*content == NULL)
    {
        return printErrorMessage(outOfMemory, "While allocating memory for content in readFile()", true);
    }

    fread(*content, sizeof(char), *fileSize, file);

    return ok;
}

static size_t parseBookFileLine(const char* const line, char** const name, char** const phone)
{
    const char* const delimiter = strchr(line, BOOK_FILE_ENTRY_DELIMITER);
    const char* const newline = strchr(line, BOOK_FILE_LINE_DELIMITER);
    if (delimiter == NULL || newline == NULL)
    {
        return 0;
    }

    const size_t nameLength = delimiter - line;
    const size_t phoneLength = newline - delimiter - 1;

    *name = (char*)calloc(nameLength + 1, sizeof(char));
    if (*name == NULL)
    {
        return 0;
    }

    *phone = (char*)calloc(phoneLength + 1, sizeof(char));
    if (*phone == NULL)
    {
        free(*name);
        return 0;
    }

    memcpy(*name, line, nameLength);
    memcpy(*phone, delimiter + 1, phoneLength);

    return (size_t)(newline - line + 1);
}

ErrorCode readAndDeserializeFile(FILE* const file, Book* const book)
{
    char* content = NULL;
    size_t fileSize = 0;

    ErrorCode error = ok;
    if (error = readFile(file, &content, &fileSize) != ok)
    {
        return error;
    }

    char* name = NULL;
    char* phone = NULL;

    size_t position = 0;

    while (position != fileSize)
    {
        const size_t newSize = parseBookFileLine(content + position, &name, &phone);
        if (newSize == 0)
        {
            break;
        }
        position += newSize;
        if ((error = addEntry(book, name, phone)) != ok)
        {
            free(name);
            free(phone);
            return error;
        }
        free(name);
        free(phone);
    }

    free(content);

    return ok;
}
