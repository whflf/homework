#pragma once

#include "errors.h"

typedef struct ListNode
{
    char* key;
    size_t count;
    struct ListNode* next;
} ListNode;

typedef struct List
{
    ListNode* head;
    size_t size;
} List;

typedef enum
{
    newElementAdded,
    existingElementRefreshed,
    failedToAdd
} ReturnCode;

// adds an element to the beginning of the list
ReturnCode append(List* const list, const char* const key, const size_t count);

// returns element key
const char* getKey(const ListNode* const element);

// deletes the list
void deleteList(List* const list);

// prints the list
void printList(const List* const list);
