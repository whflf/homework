#include <stdio.h>
#include <stdlib.h>

#include "circularList.h"

static List* createList(const list_value_t value)
{
    List* const newList = (List*)calloc(1, sizeof(List));
    if (newList == NULL)
    {
        return NULL;
    }

    newList->value = value;
    return newList;
}

ErrorCode insertElement(List** const head, const list_value_t value)
{
    List* const newNode = createList(value);
    if (newNode == NULL)
    {
        return outOfMemory;
    }

    newNode->next = *head;

    if (*head == NULL)
    {
        newNode->next = newNode;
        *head = newNode;
    }
    else
    {
        List* last = *head;
        while (last->next != *head)
        {
            last = last->next;
        }
        last->next = newNode;
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
    *head = (*head)->next;
    List* last = *head;
    while (last->next != tmpList)
    {
        last = last->next;
    }
    last->next = *head;
    free(tmpList);

    return ok;
}

void removeElement(List** const head, const List* const element)
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

    List* prev = NULL;
    List* tmpList = *head;
    do
    {
        if (tmpList == element)
        {
            if (prev)
            {
                prev->next = tmpList->next;
            }
            free(tmpList);
            break;
        }
        prev = tmpList;
        tmpList = tmpList->next;
    } while (prev != tmpList);

    return ok;
}

void printList(const List* const head)
{
    if (head != NULL)
    {
        const List* tmpList = head;
        do
        {
            printf("%d ", tmpList->value);
            tmpList = tmpList->next;
        } while (tmpList != head);
        printf("\n");
    }
    else
    {
        printf("Got an empty list! Nothing to print.\n");
    }
}

void deleteList(List* const head)
{
    if (head == NULL)
    {
        return;
    }

    List* curr = head;
    List* next = NULL;
    do
    {
        next = curr->next;
        free(curr);
        curr = next;
    } while (curr != head);
}

List* getElementAtPosition(List* const head, const int position)
{
    int positionCounter = 0;
    List* tmpList = head;
    do
    {
        if (positionCounter == position)
        {
            return tmpList;
        }
        tmpList = tmpList->next;
        ++positionCounter;
    } while (head != head->next);

    return NULL;
}
