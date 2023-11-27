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
    List* newList = calloc(1, sizeof(List));
    if (newList == NULL)
    {
        return outOfMemory;
    }
    newList->value = value;
    return newList;
}

static void changeHead(List** head, List* newNode)
{
    newNode->next = *head;
    *head = newNode;
}

size_t getSize(List* head)
{
    size_t size = 0;
    for (; head != NULL; head = head->next)
    {
        ++size;
    }
    return size;
}

static void add(List** head, List* newNode)
{
    newNode->next = (*head)->next;
    (*head)->next = newNode;
}

ErrorCode sortingInsert(List** head, const list_value_t value)
{
    if (*head == NULL)
    {
        *head = createList(value);
    }

    List* const newNode = createList(value);
    if (newNode == outOfMemory)
    {
        return outOfMemory;
    }

    if ((*head)->value >= value)
    {
        changeHead(head, newNode);
        return ok;
    }

    for (; (*head)->next != NULL; head = &(*head)->next)
    {
        if ((*head)->next->value >= value && (*head)->value <= value)
        {
            add(head, newNode);
            return ok;
        }
    }
    add(head, newNode);
    return ok;
}

static void excludeHead(List** head)
{
    List* tmpList = *head;
    *head = (*head)->next;
    free(tmpList);
}

void exclude(List** head, const list_value_t value)
{
    if (head == NULL || *head == NULL)
    {
        return;
    }

    while (*head != NULL && value == (*head)->value)
    {
        excludeHead(head);
    }

    for (; *head != NULL; head = &(*head)->next)
    {
        while ((*head)->next != NULL && (*head)->next->value == value)
        {
            List* tmpNode = (*head)->next;
            (*head)->next = (*head)->next->next;
            free(tmpNode);
        }
    }
}

void printList(const List* const head)
{
    if (head != NULL)
    {
        List* tmpList = head;
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

char* writeListToString(const List* const head)
{
    char* string = (char*)malloc(getSize(head) * 2);
    if (string == NULL)
    {
        return NULL;
    }

    if (head != NULL)
    {
        List* tmpList = head;
        for (size_t i = 0; tmpList != NULL; tmpList = tmpList->next, i += 2)
        {
            string[i] = atoi(&tmpList->value);
            string[i + 1] = tmpList->next != NULL ? ' ' : '\0';
        }
    }
    else
    {
        free(string);
        return NULL;
    }

    return string;
}

void deleteList(List** head)
{
    if (head == NULL || *head == NULL)
    {
        return;
    }

    List** headPtr = head;
    for (; (*headPtr)->next != NULL; headPtr = &(*headPtr)->next)
    {
        List* tmpNode = (*headPtr)->next;
        (*headPtr)->next = (*headPtr)->next->next;
        free(tmpNode);
    }
    if (*head != *headPtr)
    {
        free(*head);
        *head = NULL;
    }
    free(*headPtr);
    headPtr = NULL;
}
