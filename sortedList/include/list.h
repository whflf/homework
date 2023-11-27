#pragma once

#include "errors.h"

typedef int list_value_t;

typedef struct List List;

List* createList(void);

ErrorCode insert(List** head, const list_value_t value, const size_t position);

ErrorCode sortingInsert(List** head, const list_value_t value);

ErrorCode exclude(List** head, const list_value_t value);

void printList(const List* const head);

char* writeListToString(const List* const head);

ErrorCode deleteList(List** head);
