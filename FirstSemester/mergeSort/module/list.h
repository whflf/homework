#pragma once

#include "errors.h"

typedef char* ListValue;
typedef struct List List;

struct List
{
    ListValue name;
    ListValue phone;
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
ErrorCode append(List** const head, ListValue name, ListValue phone);

// gets an element by its position
List* getElement(List* head, const size_t position);

// deletes the list
void deleteList(List** const head);

// returns sorted list
List* mergeSort(List* const head, const BookSortOption option);

// prints the list
void printList(const List* head);

// converts circular list to non-circular
void convertCircularListToNonCircular(List* const head);

// clones list from existing one
List* cloneList(const List* head);
