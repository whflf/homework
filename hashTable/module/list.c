#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "list.h"
#include "errors.h"

static List* createListElement(char* const key, const int value)
{
    List* newElement = (List*)calloc(1, sizeof(List));
    if (newElement == NULL)
    {
        return NULL;
    }

    newElement->key = key;
    newElement->value = value;

    return newElement;
}

static List* getElement(List* const* const head, const char* const key)
{
    List* tmpList = *head;
    for (; tmpList != NULL; tmpList = tmpList->next)
    {
        if (strcmp(tmpList->key, key) == 0)
        {
            return tmpList;
        }
    }
    return NULL;
}

size_t getSize(const List* head)
{
    size_t size = 0;
    for (; head != NULL; head = head->next)
    {
        ++size;
    }
    return size;
}

ReturnCode append(List** const head, char* const key, const int value)
{
    if (*head == NULL)
    {
        if ((*head = createListElement(key, value)) == NULL)
        {
            return failedToAdd;
        }
        return newElementAdded;
    }

    List* const element = getElement(head, key);
    if (element != NULL)
    {
        ++element->value;
        return existingElementRefreshed;
    }

    List* const newElement = createListElement(key, value);
    if (newElement == NULL)
    {
        return newElementAdded;
    }

    newElement->next = *head;
    *head = newElement;

    return newElementAdded;
}

const char* getKey(const List* const element)
{
    return element->key;
}

void deleteList(List** const head)
{
    if (*head == NULL)
    {
        return;
    }

    while ((*head)->next != NULL)
    {
        List* const tmpNode = (*head)->next;
        free(tmpNode->key);
        (*head)->next = (*head)->next->next;
        free(tmpNode);
    }

    free((*head)->key);
    free(*head);
}

void printList(const List* head)
{
    if (head != NULL)
    {
        for (; head != NULL; head = head->next)
        {
            printf("\"%s\" - %d time%c\n", head->key, head->value, head->value == 1 ? '\0' : 's');
        }
    }
}
