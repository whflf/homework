#pragma once

#include "hashTable.h"
#include "errors.h"

#define DYNAMIC_STRING_MIN_ALLOCATION_SIZE 16

HashTable* getFrequencyTableFromFile(const char* const filename, ErrorCode* const error);
