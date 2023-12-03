#pragma once

#define BOOK_FILE_NAME "book.txt"
#define TEST_BOOK_FILE_NAME "test-book.txt"
#define BOOK_FILE_ENTRY_DELIMITER ' '
#define BOOK_FILE_ENTRY_DELIMITER_ALT '_'
#define BOOK_FILE_LINE_DELIMITER '\n'
#define ENTRY_MAX_COUNT 100

#include "errors.h"

typedef struct BookEntry
{
    char* name;
    char* phone;
} BookEntry;

typedef struct Book
{
    BookEntry entries[ENTRY_MAX_COUNT];
    size_t entryCount;
} Book;

Book* createBook(void);

void destroyBook(Book* const book);

ErrorCode addEntry(Book* const book, const char* const name, const char* const phone);

void printEntries(const Book* const book);

int findPhoneByName(const Book* const book, const char* const name);

int findNameByPhone(const Book* const book, const char* const phone);

ErrorCode saveContentToFile(const Book* const book, const char* const filename);
