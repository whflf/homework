#pragma once

#include "errors.h"
#include "list.h"

#define TABLE_INITIAL_SIZE 101
#define POLYNOMIAL_POINT 257
#define AVERAGE_LIST_LENGTH_THRESHOLD 5

typedef struct HashTable HashTable;

// initializes new hash table
HashTable* createHashTable(const size_t initialSize);

// deletes hash table
void deleteHashTable(HashTable** const table);

// returns hash table load factor
float getLoadFactor(const HashTable* const table);

// returns average length of list in hash table
size_t getAverageLength(const HashTable* const table);

// returns max length of list in hash table
size_t getMaxLength(const HashTable* const table);

// adds new entry to hash table (or updates an existing one)
ErrorCode addEntry(HashTable* const* const table, const char* const key);

// gets value from hash table by key
int getValue(const HashTable* const table, const char* const key);

// shows hash table content
void printTable(const HashTable* const table);
