#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "phoneBook.h"
#include "errors.h"
#include "fileParsing.h"
#include "tests.h"

static Book* createBookAndAddEntry(const char* const name, const char* const phone)
{
    Book* const testBook = createBook();
    if (testBook == NULL)
    {
        return NULL;
    }

    if (addEntry(testBook, name, phone) != ok)
    {
        destroyBook(testBook);
        return NULL;
    }

    return testBook;
}

static bool testGetPhone(void)
{
    char name[] = { "Michael" };
    char phone[] = { "+73837778899" };

    Book* testBook = createBookAndAddEntry(name, phone);
    if (testBook == NULL)
    {
        return false;
    }

    const int michaelIndex = findPhoneByName(testBook, name);
    if (michaelIndex == -1)
    {
        return false;
    }

    const bool result = memcmp(testBook->entries[michaelIndex].phone, phone, sizeof(phone)) == 0;

    destroyBook(testBook);
    return result;
}

static bool testGetName(void)
{
    const char name[] = { "Yuri" };
    const char phone[] = { "+78123331818" };

    Book* testBook = createBookAndAddEntry(name, phone);
    if (testBook == NULL)
    {
        return false;
    }

    const int yuriIndex = findNameByPhone(testBook, phone);

    if (yuriIndex == -1)
    {
        return false;
    }

    const bool result = memcmp(testBook->entries[yuriIndex].name, name, sizeof(name)) == 0;

    destroyBook(testBook);
    return result;
}

static bool testCorrectSaveToFile(void)
{
    const char name[] = { "Kate" };
    const char phone[] = { "+78428880696" };

    Book* testBook = createBookAndAddEntry(name, phone);
    if (testBook == NULL)
    {
        return false;
    }

    saveContentToFile(testBook, TEST_BOOK_FILE_NAME);

    FILE* file = NULL;

    fopen_s(&file, TEST_BOOK_FILE_NAME, "rb");
    if (file == NULL)
    {
        return false;
    }

    char* content = NULL;
    long fileSize = 0;
    if (readFile(file, &content, &fileSize) != ok)
    {
        return false;
    }
    fclose(file);

    char* correctContent = (char*)calloc(sizeof(name) + sizeof(phone) + 2, sizeof(char));
    if (correctContent == NULL)
    {
        return false;
    }

    memcpy(correctContent, name, sizeof(name) - 1);
    *(correctContent + sizeof(name) - 1) = BOOK_FILE_ENTRY_DELIMITER;
    memcpy(correctContent + sizeof(name), phone, sizeof(phone) - 1);
    *(correctContent + sizeof(name) + sizeof(phone) - 1) = BOOK_FILE_LINE_DELIMITER;

    const bool result = memcmp(content, correctContent, sizeof(name) + sizeof(phone)) == 0;

    free(content);
    free(correctContent);
    return result;
}

bool passTests(void)
{
    return testCorrectSaveToFile() && testGetName() && testGetPhone();
}
