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
        char strValue[MAX_DIGITS_COUNT + 1];
        itoa(head->value, strValue, 10);
        size += strlen(strValue) + 1;
    }
    return size;
}

static void add(List* const* const head, List* const newNode)
{
    newNode->next = (*head)->next;
    (*head)->next = newNode;
}

ErrorCode sortingInsert(List** head, const list_value_t value)
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

static void excludeHead(List** const head)
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

char* writeListToString(const List* const head)
{
    char* const string = (char*)malloc(getLength(head));
    if (string == NULL)
    {
        return NULL;
    }

    if (head != NULL)
    {
        const List* tmpList = head;
        for (size_t i = 0; tmpList != NULL; tmpList = tmpList->next, i += 2)
        {
            itoa(tmpList->value, &string[i], 10);
            if ()
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
    if (*head == NULL)
    {
        return;
    }

    while (*head != NULL)
    {
        List* tmpNode = *head;
        *head = (*head)->next;
        free(tmpNode);
        tmpNode = NULL;
    }
}
