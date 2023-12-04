#pragma once

#include "errors.h"

typedef int list_value_t;

typedef struct ListElement ListElement;

typedef struct List List;

//returns list size
size_t size(List* head);

//adds an element to the end of the list
ErrorCode append(List** head, const list_value_t value);

//deletes an element by its position
ErrorCode delete(List** head, const size_t position);

//prints the list
void printList(const List* const head);

//changes elements' positions after deleting
void renumber(List** head);

//deletes the list
ErrorCode deleteList(List** head);
