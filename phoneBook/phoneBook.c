#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "phoneBook.h"

Book* createBook(void)
{
    return (Book*)calloc(1, sizeof(Book));
}

void destroyBook(const Book* const book)
{
    for (size_t i = 0; i < book->entryCount; ++i)
    {
        free(book->entries[i].name);
        free(book->entries[i].phone);
    }
    free(book);
}

ErrorCode addEntry(Book* const book, const char* const name, const char* const phone)
{
    if (book->entryCount >= ENTRY_MAX_COUNT)
    {
        return entryLimitReached;
    }

    book->entries[book->entryCount].name = (char*)malloc(strlen(name) + 1);
    book->entries[book->entryCount].phone = (char*)malloc(strlen(phone) + 1);
    if (
        book->entries[book->entryCount].name == NULL ||
        book->entries[book->entryCount].phone == NULL
        )
    {
        return outOfMemory;
    }

    strcpy(book->entries[book->entryCount].name, name);
    strcpy(book->entries[book->entryCount].phone, phone);
    ++book->entryCount;

    return ok;
}

void printEntries(const Book* const book)
{
    printf("Phone book entries:\n");

    if (!book->entryCount)
    {
        printf(" No entries.\n");
        return;
    }

    for (size_t i = 0; i < book->entryCount; ++i)
    {
        printf(" %zu: %s - %s\n", i + 1, book->entries[i].name, book->entries[i].phone);
    }
}

int findPhoneByName(const Book* const book, const char* const name)
{
    int index = -1;

    for (size_t i = 0; i < book->entryCount; ++i)
    {
        if (strcmp(name, book->entries[i].name) == 0)
        {
            index = i;
            break;
        }
    }

    return index;
}

int findNameByPhone(const Book* const book, const char* const phone)
{
    int index = -1;

    for (size_t i = 0; i < book->entryCount; ++i)
    {
        if (strcmp(phone, book->entries[i].phone) == 0)
        {
            index = i;
        }
    }

    return index;
}

static size_t serializeBookContent(const Book* const book, const char** const contentPtr)
{
    size_t tempContentSize = 0, contentSize = 0;

    for (size_t i = 0; i < book->entryCount; ++i)
    {
        const size_t nameLength = strlen(book->entries[i].name);
        const size_t phoneLength = strlen(book->entries[i].phone);
        tempContentSize += nameLength + phoneLength + 2;
    }

    char* const temp = (char*)malloc(tempContentSize);
    if (temp)
    {
        for (size_t i = 0; i < book->entryCount; ++i)
        {
            const size_t nameLength = strlen(book->entries[i].name);
            const size_t phoneLength = strlen(book->entries[i].phone);
            memcpy(temp + contentSize, book->entries[i].name, nameLength);
            *(temp + contentSize + nameLength) = BOOK_FILE_ENTRY_DELIMITER;
            memcpy(temp + contentSize + nameLength + 1, book->entries[i].phone, phoneLength);
            *(temp + contentSize + nameLength + phoneLength + 1) = BOOK_FILE_LINE_DELIMITER;
            contentSize += nameLength + phoneLength + 2;
        }
        *contentPtr = temp;
    }
    return contentSize;
}

ErrorCode saveContentToFile(const Book* const book, const char* const filename)
{
    FILE* file = NULL;
    fopen_s(&file, filename, "wb");
    if (file)
    {
        char* const content = NULL;
        const size_t contentSize = serializeBookContent(book, &content);
        if (content)
        {
            fwrite(content, 1, contentSize, file);
            free(content);
            fclose(file);
            return ok;
        }
        else
        {
            fclose(file);
            return outOfMemory;
        }
    }
    else
    {
        return fileError;
    }
}
