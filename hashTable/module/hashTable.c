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
    size_t sumOfLengths;
};

static void freeBuckets(List** const array, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        free(array[i]);
    }
    free(array);
}

static ErrorCode initializeBuckets(List** const array, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        array[i] = (List*)calloc(1, sizeof(List));
        {
            if (array[i] == NULL)
            {
                freeBuckets(array, i);
                return outOfMemory;
            }
        }
    }

    return ok;
}

HashTable* createHashTable(const size_t initialSize)
{
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

    if (initializeBuckets(newTable->buckets, initialSize) == outOfMemory)
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
    free(*table);
}

float getLoadFactor(const HashTable* const table)
{
    return (float)table->numberOfEntries / (float)table->size;
}

size_t getAverageLength(const HashTable* const table)
{
    if (table->size > 0)
    {
        return table->sumOfLengths / table->size;
    }

    return 0;
}

size_t getMaxLength(const HashTable* const table)
{
    size_t maxLength = 0;
    for (size_t i = 0; i < table->size; ++i)
    {
        maxLength = table->buckets[i]->size > maxLength ? table->buckets[i]->size : maxLength;
    }

    return maxLength;
}

static size_t hash(const char* const key, const size_t tableSize)
{
    const size_t keyLength = strlen(key);
    size_t index = 0;

    for (size_t i = 0; i < keyLength; ++i)
    {
        index = (index * POLYNOMIAL_POINT + (int)(key[i])) % 1000000007 % tableSize;
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

static ErrorCode resize(HashTable* const* const table)
{
    size_t newSize = (*table)->size * 2 + 1;

    List** const newBucketsArray = (List**)calloc(newSize, sizeof(List*));
    if (newBucketsArray == NULL)
    {
        return outOfMemory;
    }

    if (initializeBuckets(newBucketsArray, newSize) == outOfMemory)
    {
        return outOfMemory;
    }

    for (size_t i = 0; i < (*table)->size; ++i)
    {
        List* currentBucket = (*table)->buckets[i];
        const ListNode* currentEntry = (*table)->buckets[i]->head;
        while (currentEntry != NULL)
        {
            const char* const currentKey = getKey(currentEntry);
            const size_t newIndex = hash(currentKey, newSize);

            const ReturnCode returnCode =
                append(newBucketsArray[newIndex], currentKey, currentEntry->count);
            if (returnCode == failedToAdd)
            {
                freeBuckets(newBucketsArray, newSize);
                return outOfMemory;
            }

            currentEntry = currentEntry->next;
        }
    }

    freeBuckets((*table)->buckets, (*table)->size);
    (*table)->size = newSize, (*table)->buckets = newBucketsArray;

    return ok;
}

ErrorCode addEntry(HashTable* const* const table, const char* const key)
{
    const size_t entryIndex = hash(key, (*table)->size);

    char* const keyCopy = copyKey(key);
    if (keyCopy == NULL)
    {
        return outOfMemory;
    }

    const ReturnCode returnCode = append((*table)->buckets[entryIndex], keyCopy, 1);

    if (returnCode == failedToAdd)
    {
        free(keyCopy);
        return outOfMemory;
    }

    if (returnCode == existingElementRefreshed)
    {
        free(keyCopy);
    }

    if (returnCode == newElementAdded)
    {
        ++(*table)->numberOfEntries;
        ++(*table)->sumOfLengths;

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
    const ListNode* entry = table->buckets[searchIndex]->head;
    if (entry != NULL)
    {
        for (; entry != NULL && strcmp(entry->key, key) != 0; entry = entry->next);
        return entry != NULL ? entry->count : 0;
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
