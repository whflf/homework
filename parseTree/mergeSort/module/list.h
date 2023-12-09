#pragma once

#include "errors.h"

typedef char ListValue;
typedef struct List List;

struct List
{
    ListValue* name;
    ListValue* phone;
    List* previous;
    List* next;
};

typedef enum {
    byName,
    byPhone
} BookSortOption;

// returns list size
size_t getSize(const List* head);

// adds an element to the end of the list
ErrorCode append(List** head, ListValue* const name, ListValue* const phone);

// gets an element by its position
List* getElement(List* const* head, const size_t position);

// deletes the list
void deleteList(List** head);

// returns sorted list
List* mergeSort(const List* const* head, const size_t left, const size_t right, const BookSortOption option);

// prints the list
void printList(const List* const head);
