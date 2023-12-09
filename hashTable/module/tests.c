#include <stdlib.h>

#include "fileParsing.h"
#include "tests.h"

#define FIRST_TEST_FILE_NAME "testFiles/test-long-text.txt"
#define SECOND_TEST_FILE_NAME "testFiles/test-empty-file.txt"

static bool testLongText(void)
{
    ErrorCode error = ok;
    HashTable* testTable = getFrequencyTableFromFile(FIRST_TEST_FILE_NAME, &error);
    if (error != ok)
    {
        return false;
    }

    const size_t numberOfWords = 5;
    const char* const keys[] = { "the", "members", "Tyler", "and", "tesseract" };
    const int correctFrequencies[] = { 18, 1, 7, 9, 0 };

    for (size_t i = 0; i < numberOfWords; ++i)
    {
        if (getValue(testTable, keys[i]) != correctFrequencies[i])
        {
            deleteHashTable(&testTable);
            return false;
        }
    }

    const bool result = (getLoadFactor(testTable) - 0.98104268 < 3e-8) && getAverageLength(testTable) == 1 && getMaxLength(testTable) == 4;
    deleteHashTable(&testTable);

    return result;
}

static bool testEmptyFile(void)
{
    ErrorCode error = ok;
    HashTable* testTable = getFrequencyTableFromFile(SECOND_TEST_FILE_NAME, &error);
    if (error != ok)
    {
        return false;
    }

    const bool result = getLoadFactor(testTable) == 0 &&
        getAverageLength(testTable) == 0 &&
        getMaxLength(testTable) == 0;

    deleteHashTable(&testTable);
    return result;
}

bool passTests(void)
{
    return testLongText() && testEmptyFile();
}
