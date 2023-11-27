#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "phoneBook.h"
#include "errors.h"
#include "fileParsing.h"

ErrorCode readFile(FILE* file, char** content, long* const fileSize)
{
    fseek(file, 0, SEEK_END);

    *fileSize = ftell(file);
    if (*fileSize == -1L)
    {
        printf("File error occurred. Exiting.\n");
        return fileError;
    }

    fseek(file, 0, SEEK_SET);

    *content = (char*)calloc((size_t)*fileSize + 1, sizeof(char));
    if (*content == NULL)
    {
        return outOfMemory;
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

    *name = (char*)malloc(nameLength + 1);
    if (*name == NULL)
    {
        return 0;
    }

    *phone = (char*)malloc(phoneLength + 1);
    if (*phone == NULL)
    {
        return 0;
    }

    memcpy(*name, line, nameLength);
    memcpy(*phone, delimiter + 1, phoneLength);
    (*name)[nameLength] = '\0';
    (*phone)[phoneLength] = '\0';

    return (size_t)(newline - line + 1);
}

ErrorCode readAndSerializeFile(FILE* file, Book* const book)
{
    char* content = NULL;
    long fileSize = 0;

    ErrorCode error = ok;
    if (error = readFile(file, &content, &fileSize) != ok)
    {
        return error;
    }

    if (content)
    {
        char* name = NULL;
        char* phone = NULL;

        size_t position = 0;

        while (position != fileSize && (position += parseBookFileLine(content + position, &name, &phone)))
        {
            addEntry(book, name, phone);
            free(name);
            free(phone);
        }

        free(content);
    }

    return ok;
}

