#define _CRT_RAND_S

#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

#include "fileParsing.h"
#include "tests.h"

#define STRING_LENGTH 5
#define STRING_NUMBER 100000

#define FIRST_TEST_FILE_NAME "testFiles/test-long-text.txt"
#define SECOND_TEST_FILE_NAME "testFiles/test-empty-file.txt"

static char* generateString(const size_t length)
{
    const char* const characters = "QqWwEeRrTtYyUuIiOoPpAaSsDdFfGgHhJjKkLlZzXxCcVvBbNnMm0123456789/*-+=/.,?!()_";
    const size_t charactersLength = strlen(characters);
    char* const randomString = (char*)calloc(length + 1, sizeof(char));
    if (randomString == NULL)
    {
        return NULL;
    }

    unsigned int value = 0;
    for (size_t i = 0; i < length; ++i)
    {
        rand_s(&value);
        randomString[i] = characters[(size_t)((double)value / ((double)UINT_MAX + 1) * charactersLength)];
    }

    return randomString;
}

static void freeStringArray(char* const* const array, const size_t upperIndex)
{
    for (size_t i = 0; i < upperIndex; ++i)
    {
        free(array[i]);
    }
    free(array);
}

static char** getRandomStringArray(void)
{
    char** const strings = (char**)calloc(STRING_NUMBER, sizeof(char*));
    if (strings == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < STRING_NUMBER; ++i)
    {
        strings[i] = generateString(STRING_LENGTH);
        if (strings[i] == NULL)
        {
            freeStringArray(strings, i);
            return NULL;
        }
    }

    return strings;
}

static bool loadTest(void)
{
    const char* const* const strings = getRandomStringArray();
    if (strings == NULL)
    {
        return false;
    }

    HashTable* table = createHashTable(TABLE_INITIAL_SIZE);
    clock_t start = clock();

    for (size_t i = 0; i < STRING_NUMBER; ++i)
    {
        if (addEntry(&table, strings[i]) == outOfMemory)
        {
            deleteHashTable(&table);
            freeStringArray(strings, STRING_NUMBER);
            return false;
        }
    }

    clock_t stop = clock();
    deleteHashTable(&table);

    return (double)(stop - start) / CLOCKS_PER_SEC <= 3.0;
}

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
    return loadTest() && testLongText() && testEmptyFile();
}
