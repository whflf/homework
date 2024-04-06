#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "errors.h"

struct List
{
    list_value_t value;
    struct List* next;
};

static List* createList(const list_value_t value)
{
    List* const newList = calloc(1, sizeof(List));
    if (newList == NULL)
    {
        return NULL;
    }

    newList->value = value;

    return newList;
}

static void changeHead(List** const head, List* const newNode)
{
    newNode->next = *head;
    *head = newNode;
}

size_t getLength(const List* head)
{
    size_t size = 0;
    for (; head != NULL; head = head->next)
    {
        ++size;
    }
    return size;
}

static void add(List* const head, List* const newNode)
{
    newNode->next = head->next;
    head->next = newNode;
}

ErrorCode sortingInsert(List** const head, const list_value_t value)
{
    if (*head == NULL)
    {
        *head = createList(value);
        return *head == NULL ? outOfMemory : ok;
    }

    List* const newNode = createList(value);
    if (newNode == NULL)
    {
        return outOfMemory;
    }

    if ((*head)->value >= value)
    {
        changeHead(head, newNode);
        return ok;
    }

    List* tmpList = *head;
    for (; tmpList->next != NULL; tmpList = tmpList->next)
    {
        if (tmpList->next->value >= value && tmpList->value <= value)
        {
            add(tmpList, newNode);
            return ok;
        }
    }

    add(tmpList, newNode);
    return ok;
}

static void excludeHead(List** const head)
{
    List* tmpList = *head;
    *head = (*head)->next;
    free(tmpList);
}

void exclude(List** const head, const list_value_t value)
{
    if (head == NULL || *head == NULL)
    {
        return;
    }

    while (*head != NULL && value == (*head)->value)
    {
        excludeHead(head);
    }

    List* tmpList = *head;
    if (tmpList != NULL)
    {
        for (; tmpList->next != NULL; tmpList = tmpList->next)
        {
            while (tmpList->next != NULL && tmpList->next->value == value)
            {
                List* tmpNode = tmpList->next;
                tmpList->next = tmpList->next->next;
                free(tmpNode);
            }
        }
    }
}

void printList(const List* const head)
{
    if (head != NULL)
    {
        const List* tmpList = head;
        for (; tmpList != NULL; tmpList = tmpList->next)
        {
            printf("%d%s", tmpList->value, tmpList->next == NULL ? "\n" : ", ");
        }
    }
    else
    {
        printf("Got an empty list! Nothing to print\n");
    }
}

int* writeListToArray(const List* const head)
{
    if (head != NULL)
    {
        int* const vector = (int*)malloc(getLength(head) * sizeof(int));
        if (vector == NULL)
        {
            return NULL;
        }

        const List* tmpList = head;
        for (size_t i = 0; tmpList != NULL; tmpList = tmpList->next, ++i)
        {
            vector[i] = tmpList->value;
        }

        return vector;
    }

    return NULL;
}


void deleteList(List** const head)
{
    while (*head != NULL)
    {
        exclude(head, (*head)->value);
    }
}

