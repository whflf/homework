#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "errors.h"

struct ListElement
{
    list_value_t value;
    size_t position;
    struct ListElement* next;
};

struct List
{
    ListElement* head;
    size_t size;
};

static ListElement* createListElement(const list_value_t value, const size_t position)
{
    ListElement* newElement = (ListElement*)calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        return NULL;
    }
    newElement->value = value;
    newElement->position = position;
    return newElement;
}

static List* createList(void)
{
    List* newList = (List*)calloc(1, sizeof(List));
    if (newList == NULL)
    {
        return NULL;
    }
    return newList;
}

size_t size(List* head)
{
    return head->size;
}

ErrorCode append(List** head, const list_value_t value)
{
    if (*head == NULL)
    {
        ListElement* const newNode = createListElement(value, 0);
        *head = createList();
        if (*head == NULL)
        {
            return outOfMemory;
        }
        (*head)->head = newNode;
        (*head)->size = 1;
        return ok;
    }

    ListElement* const newNode = createListElement(value, (*head)->size);
    if (newNode == outOfMemory)
    {
        return outOfMemory;
    }

    ListElement* currentElement = (*head)->head;
    for (; currentElement->next != NULL; currentElement = currentElement->next)
    {
        continue;
    }
    currentElement->next = newNode;
    ++(*head)->size;
    return ok;
}

ErrorCode delete(List** head, const size_t position)
{
    if (*head == NULL)
    {
        return listIsEmpty;
    }

    ListElement* currentElement = (*head)->head;
    for (; currentElement != NULL; currentElement = currentElement->next)
    {
        if (currentElement->next != NULL && currentElement->next->position == position)
        {
            ListElement* tmpNode = currentElement->next;
            currentElement->next = currentElement->next->next;
            free(tmpNode);
            break;
        }
    }
    --(*head)->size;
    renumber(head);
    return ok;
}

void printList(const List* const head)
{
    if (head != NULL)
    {
        ListElement* tmpList = head->head;
        for (; tmpList != NULL; tmpList = tmpList->next)
        {
            printf("%d ", tmpList->value);
        }
        printf("\n");
    }
    else
    {
        printf("Got an empty list! Nothing to print\n");
    }
}

static void renumber(List** head)
{
    ListElement* currentElement = (*head)->head;
    for (size_t i = 0; currentElement != NULL; currentElement = currentElement->next, ++i)
    {
        currentElement->position = i;
    }
}

ErrorCode deleteList(List** head)
{
    if (*head == NULL)
    {
        return listIsEmpty;
    }

    ListElement* currentElement = (*head)->head;
    for (; currentElement->next != NULL; currentElement = currentElement->next)
    {
        ListElement* tmpNode = currentElement->next;
        currentElement->next = currentElement->next->next;
        free(tmpNode);
        if (currentElement->next == NULL)
        {
            break;
        }

    }
    free(currentElement);
    free(*head);
    *head = NULL;
    return ok;
}
