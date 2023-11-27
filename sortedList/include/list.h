#pragma once

#include "errors.h"

typedef int list_value_t;

typedef struct List List;

List* createList(const list_value_t value);

size_t getSize(List* head);

ErrorCode sortingInsert(List** head, const list_value_t value);

void exclude(List** head, const list_value_t value);

void printList(const List* const head);

char* writeListToString(const List* const head);

void deleteList(List** head);
