#include <stdio.h>
#include <stdlib.h>

#include "circularList.h"

struct CircularList
{
    ListValue value;
    List* previous;
    List* next;
};

static List* createNode(const ListValue value)
{
    List* const newList = (List*)calloc(1, sizeof(List));
    if (newList == NULL)
    {
        return NULL;
    }

    newList->value = value;
    return newList;
}

ErrorCode insertElement(List** const head, const ListValue value)
{
    List* const newNode = createNode(value);
    if (newNode == NULL)
    {
        return outOfMemory;
    }

    if (*head == NULL)
    {
        newNode->previous = newNode->next = newNode;
        *head = newNode;
    }
    else
    {
        newNode->next = *head;
        newNode->previous = (*head)->previous;
        newNode->previous->next = newNode;
        (*head)->previous = newNode;
    }

    return ok;
}

static void removeHead(List** const head)
{
    if (head == NULL || *head == NULL)
    {
        return;
    }

    List* const tmpList = *head;
    *head = tmpList->next;
    (*head)->previous = tmpList->previous;
    (*head)->previous->next = *head;
    free(tmpList);
}

void removeElement(List** const head, List* const element)
{
    if (head == NULL || *head == NULL)
    {
        return;
    }

    if (element == *head)
    {
        removeHead(head);
        return;
    }

    element->previous->next = element->next;
    element->next->previous = element->previous;
    free(element);
}

void printList(const List* const head)
{
    if (head != NULL)
    {
        const List* tmpList = head;
        do
        {
            printf("%zu ", tmpList->value);
            tmpList = tmpList->next;
        } while (tmpList != head);
        printf("\n");
    }
    else
    {
        printf("Got an empty list! Nothing to print.\n");
    }
}

void deleteList(List** const head)
{
    if (*head == NULL)
    {
        return;
    }

    List* current = *head;
    List* next = NULL;
    do
    {
        next = current->next;
        free(current);
        current = next;
    } while (current != *head);

    *head = NULL;
}

ListValue getValue(const List* const head)
{
    return head == NULL ? (ListValue)0 : head->value;
}

List* getNext(const List* const head)
{
    return head == NULL ? NULL : head->next;
}

