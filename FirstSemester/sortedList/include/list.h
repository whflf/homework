#pragma once

#include "errors.h"

typedef int list_value_t;

typedef struct List List;

List* createList(const list_value_t value);

size_t getLength(const List* head);

ErrorCode sortingInsert(List** const head, const list_value_t value);

void exclude(List** const head, const list_value_t value);

void printList(const List* const head);

int* writeListToArray(const List* const head);

void deleteList(List** const head);
