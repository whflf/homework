#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"
#include "errors.h"

static List* createListElement(ListValue name, ListValue phone)
{
    List* const newElement = (List*)calloc(1, sizeof(List));
    if (newElement == NULL)
    {
        return NULL;
    }

    newElement->name = name;
    newElement->phone = phone;

    return newElement;
}

size_t getSize(const List* head)
{
    size_t size = 0;
    while (head != NULL)
    {
        ++size;
        head = head->next;
    }
    return size;
}

void convertCircularListToNonCircular(List* const head)
{
    if (head != NULL)
    {
        head->previous = head->previous->next = NULL;
    }
}

ErrorCode append(List** const head, ListValue name, ListValue phone)
{
    List* const newElement = createListElement(name, phone);
    if (newElement == NULL)
    {
        return outOfMemory;
    }

    if (*head == NULL)
    {
        newElement->previous = newElement->next = newElement;
        *head = newElement;
    }
    else
    {
        newElement->next = *head;
        newElement->previous = (*head)->previous;
        newElement->previous->next = newElement;
        (*head)->previous = newElement;
    }

    return ok;
}

List* getElement(List* head, const size_t position)
{
    size_t tempPosition = 0;
    do
    {
        if (tempPosition == position)
        {
            return head;
        }
        ++tempPosition;
        head = head->next;
    } while (head != NULL);

    return NULL;
}

static ListValue copyString(const ListValue string)
{
    ListValue const newString = (ListValue)malloc(strlen(string) + 1);
    if (newString == NULL)
    {
        return NULL;
    }
    strcpy(newString, string);
    return newString;
}

List* cloneList(const List* head)
{
    List* clonedList = NULL;
    while (head != NULL)
    {
        ListValue clonedName = copyString(head->name);
        ListValue clonedPhone = copyString(head->phone);
        if (append(&clonedList, clonedName, clonedPhone) != ok)
        {
            free(clonedName);
            free(clonedPhone);
            return NULL;
        }
        head = head->next;
    }
    convertCircularListToNonCircular(clonedList);
    return clonedList;
}

void deleteList(List** const head)
{
    if (*head == NULL)
    {
        return;
    }

    List* next = NULL;
    do
    {
        next = (*head)->next;
        free((*head)->name);
        free((*head)->phone);
        free(*head);
        *head = next;
    } while (*head != NULL);
}

static List* merge(List* left, List* right, const BookSortOption option)
{
    List* head = NULL;
    List* tail = NULL;

    while (left && right)
    {
        ListValue firstValue = option == byName ? left->name : left->phone;
        ListValue secondValue = option == byName ? right->name : right->phone;

        if (strcmp(firstValue, secondValue) <= 0)
        {
            if (head == NULL)
            {
                head = createListElement(left->name, left->phone);
                tail = head;
            }
            else
            {
                tail->next = left;
                left->previous = tail;
                tail = left;
            }
            left = left->next;
        }
        else
        {
            if (head == NULL)
            {
                head = createListElement(right->name, right->phone);
                tail = head;
            }
            else
            {
                tail->next = right;
                right->previous = tail;
                tail = right;
            }
            right = right->next;
        }
    }

    if (left)
    {
        tail->next = left;
        left->previous = tail;
    }
    else if (right)
    {
        tail->next = right;
        right->previous = tail;
    }

    return head;
}

List* mergeSort(List* const head, const BookSortOption option)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    List* slow = head;
    List* fast = head->next;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    List* rightHead = slow->next;
    slow->next = NULL;

    List* left = mergeSort(head, option);
    List* right = mergeSort(rightHead, option);

    return merge(left, right, option);
}

void printList(const List* head)
{
    if (head != NULL)
    {
        printf("Entries:\n");
        do
        {
            printf("- Name:  %s\n  Phone: %s\n\n", head->name, head->phone);
            head = head->next;
        } while (head != NULL);
    }
    else
    {
        printf("Got an empty list! Nothing to print\n");
    }
}
