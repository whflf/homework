#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "list.h"
#include "errors.h"

static ListNode* createListElement(char* const key, const size_t count)
{
    ListNode* newElement = (ListNode*)calloc(1, sizeof(ListNode));
    if (newElement == NULL)
    {
        return NULL;
    }

    newElement->key = key;
    newElement->count = count;

    return newElement;
}

static ListNode* getElement(const List* const list, const char* const key)
{
    ListNode* currentNode = list->head;
    for (; currentNode != NULL; currentNode = currentNode->next)
    {
        if (strcmp(currentNode->key, key) == 0)
        {
            return currentNode;
        }
    }
    return NULL;
}

ReturnCode append(List* const list, const char* const key, const size_t count)
{
    if (list->head == NULL)
    {
        if ((list->head = createListElement(key, count)) == NULL)
        {
            return failedToAdd;
        }
        ++list->size;
        return newElementAdded;
    }

    ListNode* const element = getElement(list, key);
    if (element != NULL)
    {
        ++element->count;
        return existingElementRefreshed;
    }

    ListNode* const newElement = createListElement(key, count);
    if (newElement == NULL)
    {
        return failedToAdd;
    }

    newElement->next = list->head;
    list->head = newElement;
    ++list->size;

    return newElementAdded;
}

const char* getKey(const ListNode* const element)
{
    return element->key;
}

void deleteList(List* const list)
{
    if (list == NULL || list->head)
    {
        return;
    }

    while (list->head != NULL)
    {
        ListNode* const tmpNode = list->head;
        free(tmpNode->key);
        list->head = list->head->next;
        free(tmpNode);
    }

    free(list);
}

void printList(const List* const list)
{
    ListNode* head = list->head;
    if (head != NULL)
    {
        for (; head != NULL; head = list->head->next)
        {
            printf("\"%s\" - %llu time%c\n", head->key, head->count, head->count == 1 ? '\0' : 's');
        }
    }
}
