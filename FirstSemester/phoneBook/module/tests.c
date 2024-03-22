#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "phoneBook.h"
#include "errors.h"
#include "fileParsing.h"
#include "tests.h"

static Book* createBookAndAddEntries(
    const char* const* const names,
    const char* const* const phones,
    const size_t size
)
{
    Book* testBook = createBook();
    if (testBook == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < size; ++i)
    {
        if (addEntry(testBook, names[i], phones[i]) != ok)
        {
            destroyBook(testBook);
            return NULL;
        }
    }

    return testBook;
}

static bool testGetPhone(void)
{
    char* const names[] = { "Michael", "Yuri" };
    char* const phones[] = { "+73837778899", "+78123331818" };

    Book* testBook = createBookAndAddEntries(names, phones, 2);
    if (testBook == NULL)
    {
        return false;
    }

    const int michaelIndex = findEntry(testBook, names[0], true);
    const int yuriIndex = findEntry(testBook, names[1], true);
    if (michaelIndex == -1 || yuriIndex == -1)
    {
        return false;
    }

    const bool result =
        memcmp(testBook->entries[michaelIndex].phone, phones[0], strlen(phones[0])) == 0 &&
        memcmp(testBook->entries[yuriIndex].phone, phones[1], strlen(phones[1])) == 0;

    destroyBook(testBook);
    return result;
}

static bool testGetName(void)
{
    char* const names[] = { "Yuri", "Michael" };
    char* const phones[] = { "+78123331818", "+73837778899" };

    Book* testBook = createBookAndAddEntries(names, phones, 2);
    if (testBook == NULL)
    {
        return false;
    }

    const int yuriIndex = findEntry(testBook, phones[0], false);
    const int michaelIndex = findEntry(testBook, phones[1], false);
    if (yuriIndex == -1 || michaelIndex == -1)
    {
        return false;
    }

    const bool result =
        memcmp(testBook->entries[yuriIndex].name, names[0], strlen(names[0])) == 0 &&
        memcmp(testBook->entries[michaelIndex].name, names[1], strlen(names[1])) == 0;

    destroyBook(testBook);
    return result;
}

static bool testCorrectSaveToFile(void)
{
    const char* const names[] = { "Kate", "Fox Mulder" };
    const char* const phones[] = { "+78428880696", "555-3574" };

    Book* testBook = createBookAndAddEntries(names, phones, 2);
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
    size_t fileSize = 0;
    if (readFile(file, &content, &fileSize) != ok)
    {
        return false;
    }
    fclose(file);

    const char* const correctContent = "Kate +78428880696\nFox_Mulder 555-3574\n";

    const bool result = memcmp(content, correctContent, strlen(correctContent)) == 0;

    free(content);
    return result;
}

bool passTests(void)
{
    return testGetName() && testGetPhone() && testCorrectSaveToFile();
}
