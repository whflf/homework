#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "hashTable.h"

struct HashTable
{
    size_t size;
    size_t numberOfEntries;
    List** buckets;
    size_t* listLengths;
    size_t maxLength;
    size_t sumOfLengths;
};

HashTable* createHashTable(void)
{
    const size_t initialSize = 101; 

    HashTable* newTable = (HashTable*)calloc(1, sizeof(HashTable));
    if (newTable == NULL)
    {
        return NULL;
    }

    newTable->buckets = (List**)calloc(initialSize, sizeof(List*));
    if (newTable->buckets == NULL)
    {
        deleteHashTable(&newTable);
        return NULL;
    }

    newTable->listLengths = (size_t*)calloc(initialSize, sizeof(size_t));
    if (newTable->listLengths == NULL)
    {
        deleteHashTable(&newTable);
        return NULL;
    }

    newTable->size = initialSize;

    return newTable;
}

void deleteHashTable(HashTable** const table)
{
    for (size_t i = 0; i < (*table)->size; ++i)
    {
        deleteList(&(*table)->buckets[i]);
    }

    free((*table)->buckets);
    free((*table)->listLengths);
    free(*table);
}

float getLoadFactor(const HashTable* const table)
{
    return (float)table->numberOfEntries / (float)table->size;
}

size_t getAverageLength(const HashTable* const table)
{
    if (table->numberOfEntries > 0)
    {
        return table->sumOfLengths / table->numberOfEntries;
    }

    return 0;
}

size_t getMaxLength(const HashTable* const table)
{
    return table->maxLength;
}

static bool isPrime(const unsigned long long number)
{
    for (int i = 2; i <= number / 2; ++i)
    {
        if (number % i == 0)
        {
            return false;
        }
    }

    return true;
}

static void makePrime(size_t* const size)
{
    for (; !isPrime(*size); ++(*size));
}

static size_t hash(const char* const key, const size_t tableSize)
{
    const size_t keyLength = strlen(key);
    size_t index = 0;

    for (size_t i = 0; i < keyLength; ++i)
    {
        index = (index * POLYNOMIAL_POINT + (int)(key[i])) % tableSize;
    }

    return index;
}

static char* copyKey(const char* const key)
{
    char* const copiedKey = (char*)malloc(strlen(key) + 1);
    if (copiedKey == NULL)
    {
        free(copiedKey);
        return NULL;
    }

    strcpy(copiedKey, key);
    return copiedKey;
}


static ErrorCode recalculateListLengths(HashTable* const* const table)
{
    size_t* const newLengthsArray = (size_t*)calloc((*table)->size, sizeof(size_t));
    if (newLengthsArray == NULL)
    {
        return outOfMemory;
    }

    (*table)->maxLength = 0, (*table)->sumOfLengths = 0;

    for (size_t i = 0; i < (*table)->size; ++i)
    {
        newLengthsArray[i] = getSize((*table)->buckets[i]);
        if (newLengthsArray[i] > (*table)->maxLength)
        {
            (*table)->maxLength = newLengthsArray[i];
        }
        (*table)->sumOfLengths += newLengthsArray[i];
    }

    free((*table)->listLengths);
    (*table)->listLengths = newLengthsArray;

    return ok;
}

static ErrorCode resize(HashTable* const* const table)
{
    size_t newSize = (*table)->size * 2 + 1;
    makePrime(&newSize);

    List** const newBucketsArray = (List**)calloc(newSize, sizeof(List*));
    if (newBucketsArray == NULL)
    {
        return outOfMemory;
    }

    for (size_t i = 0; i < (*table)->size; ++i)
    {
        List* currentBucket = (*table)->buckets[i];
        const List* currentEntry = (*table)->buckets[i];
        while (currentEntry != NULL)
        {
            const char* const currentKey = getKey(currentEntry);
            const size_t newIndex = hash(currentKey, newSize);

            const ReturnCode returnCode =
                append(&newBucketsArray[newIndex], copyKey(currentKey), currentEntry->value);
            if (returnCode == failedToAdd)
            {
                return outOfMemory;
            }

            currentEntry = currentEntry->next;
        }

        deleteList(&currentBucket);
    }

    free((*table)->buckets);
    (*table)->size = newSize, (*table)->buckets = newBucketsArray;

    if (recalculateListLengths(table) == outOfMemory)
    {
        return outOfMemory;
    }

    return ok;
}

ErrorCode addEntry(HashTable* const* const table, const char* const key)
{
    const size_t entryIndex = hash(key, (*table)->size);

    const ReturnCode returnCode = append(&(*table)->buckets[entryIndex], copyKey(key), 1);

    if (returnCode == failedToAdd)
    {
        return outOfMemory;
    }

    if (returnCode == newElementAdded)
    {
        ++(*table)->numberOfEntries;
        ++(*table)->sumOfLengths;

        if (++(*table)->listLengths[entryIndex] > (*table)->maxLength)
        {
            (*table)->maxLength = (*table)->listLengths[entryIndex];
        }

        if (getAverageLength(*table) >= AVERAGE_LIST_LENGTH_THRESHOLD || getLoadFactor(*table) > 1.0)
        {
            if (resize(table) == outOfMemory)
            {
                return outOfMemory;
            }
        }
    }

    return ok;
}

int getValue(const HashTable* const table, const char* const key)
{
    const size_t searchIndex = hash(key, table->size);
    const List* entry = table->buckets[searchIndex];
    if (entry != NULL)
    {
        for (; entry != NULL && strcmp(entry->key, key) != 0; entry = entry->next);
        return entry != NULL ? entry->value : 0;
    }

    return 0;
}

void printTable(const HashTable* const table)
{
    if (table->numberOfEntries > 0)
    {
        for (size_t i = 0; i < table->size; ++i)
        {
            printList(table->buckets[i]);
        }
    }
    else
    {
        printf("No words were detected.\n");
    }
}
