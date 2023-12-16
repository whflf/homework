#pragma once

#include <stdlib.h>
#include "errors.h"

typedef size_t ListValue;

typedef struct CircularList List;

ErrorCode insertElement(List** const head, const ListValue value);

void removeElement(List** const head, List* const element);

void printList(const List* const head);

void deleteList(List** const head);

ListValue getValue(const List* const head);

List* getNext(const List* const head);

