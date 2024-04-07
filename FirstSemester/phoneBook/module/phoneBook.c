#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

#include "phoneBook.h"

Book* createBook(void)
{
    return (Book*)calloc(1, sizeof(Book));
}

void destroyBook(Book* const book)
{
    for (size_t i = 0; i < book->entryCount; ++i)
    {
        free(book->entries[i].name);
        free(book->entries[i].phone);
    }
    free(book);
}

static void replaceCharacterOccurrences(char* const string, const char match, const char replace)
{
    const size_t length = strlen(string);
    for (size_t i = 0; i <= length; ++i)
    {
        if (string[i] == match)
        {
            string[i] = replace;
        }
    }
}

ErrorCode addEntry(Book* const book, const char* const name, const char* const phone)
{
    if (book->entryCount >= ENTRY_MAX_COUNT)
    {
        return entryLimitReached;
    }

    book->entries[book->entryCount].name = (char*)malloc(strlen(name) + 1);
    book->entries[book->entryCount].phone = (char*)malloc(strlen(phone) + 1);

    char* entryName = book->entries[book->entryCount].name;
    char* entryPhone = book->entries[book->entryCount].phone;

    if (entryName == NULL || entryPhone == NULL)
    {
        free(entryName);
        free(entryPhone);
        return outOfMemory;
    }

    strcpy(entryName, name);
    strcpy(entryPhone, phone);

    replaceCharacterOccurrences(entryName, BOOK_FILE_ENTRY_DELIMITER, BOOK_FILE_ENTRY_DELIMITER_ALT);
    replaceCharacterOccurrences(entryPhone, BOOK_FILE_ENTRY_DELIMITER, BOOK_FILE_ENTRY_DELIMITER_ALT);

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

int findEntry(const Book* const book, char* const string, const bool toFindPhone)
{
    int index = -1;

    replaceCharacterOccurrences(string, BOOK_FILE_ENTRY_DELIMITER, BOOK_FILE_ENTRY_DELIMITER_ALT);

    for (size_t i = 0; i < book->entryCount; ++i)
    {
        if (strcmp(string, toFindPhone ? book->entries[i].name : book->entries[i].phone) == 0)
        {
            index = (int)i;
            break;
        }
    }

    return index;
}

static void serializeAndWriteBookContent(const Book* const book, FILE* const file)
{
    for (size_t i = 0; i < book->entryCount; ++i)
    {
        fprintf(
            file, "%s%c%s%c",
            book->entries[i].name, BOOK_FILE_ENTRY_DELIMITER,
            book->entries[i].phone, BOOK_FILE_LINE_DELIMITER
        );
    }
}

ErrorCode saveContentToFile(const Book* const book, const char* const filename)
{
    FILE* file = NULL;
    fopen_s(&file, filename, "w");
    if (file)
    {
        fclose(file);
    }
    fopen_s(&file, filename, "ab");
    if (file)
    {
        serializeAndWriteBookContent(book, file);
        fclose(file);
        return ok;
    }
    else
    {
        return fileError;
    }
}
