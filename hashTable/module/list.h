#pragma once

#include "errors.h"

typedef struct List List;

struct List
{
    char* key;
    int value;
    List* next;
};

typedef enum
{
    newElementAdded,
    existingElementRefreshed,
    failedToAdd
} ReturnCode;

// returns list size
size_t getSize(const List* head);

// adds an element to the beginning of the list
ErrorCode append(List** const head, char* const key, const int value);

// returns element key
const char* getKey(const List* const element);

// deletes the list
void deleteList(List** head);

// prints the list
void printList(const List* const head);
