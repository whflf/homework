#pragma once

typedef int list_value_t;


typedef struct List
{
    list_value_t value;
    struct List* next;
} List;

typedef enum
{
    ok,
    listIsEmpty,
    outOfMemory,
    wrongInput,
    testsFailed
} ErrorCode;

ErrorCode insertElement(List** const head, const list_value_t value);

void removeElement(List** const head, const List* const element);

void printList(const List* const head);

void deleteList(List* const head);

List* getElementAtPosition(List* const head, const int position);
