#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"
#include "errors.h"

static List* createListElement(ListValue* const name, ListValue* const phone)
{
    List* newElement = (List*)calloc(1, sizeof(List));
    if (newElement == NULL)
    {
        return NULL;
    }

    newElement->name = name;
    newElement->phone = phone;
    newElement->previous = newElement->next = newElement;

    return newElement;
}

size_t getSize(const List* const head)
{
    size_t size = 0;
    if (head != NULL)
    {
        List* tempNode = head;
        do
        {
            ++size;
            tempNode = tempNode->next;
        } while (tempNode != head);
    }
    return size;
}

ErrorCode append(List** head, ListValue* const name, ListValue* const phone)
{
    List* const newElement = createListElement(name, phone);
    if (newElement == NULL)
    {
        return outOfMemory;
    }

    if (*head == NULL)
    {
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

List* getElement(List* const* head, const size_t position)
{
    List* tempNode = *head;
    size_t tempPosition = 0;
    do
    {
        if (tempPosition == position) return tempNode;
        ++tempPosition;
        tempNode = tempNode->next;
    } while (tempNode != *head);

    return NULL;
}

static bool isInList(List* const head, ListValue* const name, ListValue* const phone)
{
    if (head != NULL)
    {
        List* tempNode = head;
        do
        {
            if (strcmp(name, tempNode->name) == 0 && strcmp(phone, tempNode->phone) == 0) return true;
            tempNode = tempNode->next;
        } while (tempNode != head);
    }

    return false;
}

static char* copyName(const List* const element)
{
    char* const name = (char*)malloc(strlen(element->name) + 1);
    if (name == NULL)
    {
        return NULL;
    }

    strcpy(name, element->name);
    return name;
}

static char* copyPhone(const List* const element)
{
    char* const phone = (char*)malloc(strlen(element->phone) + 1);
    if (phone == NULL)
    {
        return NULL;
    }

    strcpy(phone, element->phone);
    return phone;
}

void deleteList(List** head)
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
        free(current->name);
        free(current->phone);
        free(current);
        current = next;
    } while (current != *head);

    *head = NULL;
}

List* mergeSort(const List* const* head, const size_t left, const size_t right, const BookSortOption option)
{
    if (left + 1 == right)
    {
        const List* const tmpElement = getElement(head, left);

        List* const element = createListElement(copyName(tmpElement), copyPhone(tmpElement));
        if (element == NULL)
        {
            return NULL;
        }

        return element;
    }

    const size_t middle = left + (right - left) / 2;

    List* firstElement = mergeSort(head, left, middle, option);
    List* secondElement = mergeSort(head, middle, right, option);
    if (firstElement == NULL || secondElement == NULL)
    {
        free(firstElement);
        free(secondElement);
        return NULL;
    }

    List* firstList = firstElement;
    List* secondList = secondElement;
    const size_t firstListSize = getSize(firstList), 
                 secondListSize = getSize(secondList);

    List* mergedList = NULL;

    ListValue* firstValue = NULL;
    ListValue* secondValue = NULL;

    do
    {
        if (option == byName)
        {
            firstValue = firstElement->name;
            secondValue = secondElement->name;
        }
        else
        {
            firstValue = firstElement->phone;
            secondValue = secondElement->phone;
        }
        if (
            !isInList(mergedList, firstElement->name, firstElement->phone) &&
            (strcmp(firstValue, secondValue) <= 0 || isInList(mergedList, secondElement->name, secondElement->phone))
            )
        {
            if (append(&mergedList, copyName(firstElement), copyPhone(firstElement)) == outOfMemory)
            {
                return NULL;
            }
            firstElement = firstElement->next;
        }
        else
        {
            if (append(&mergedList, copyName(secondElement), copyPhone(secondElement)) == outOfMemory)
            {
                return NULL;
            }
            secondElement = secondElement->next;
        }
    } while (firstElement != firstList || secondElement != secondList || getSize(mergedList) != firstListSize + secondListSize);

    deleteList(&firstList);
    deleteList(&secondList);

    return mergedList;
}

void printList(const List* const head)
{
    if (head != NULL)
    {
        List* tmpList = head;
        printf("Entries:\n");
        do
        {
            printf("  Name:  %s\n  Phone: %s\n\n", tmpList->name, tmpList->phone);
            tmpList = tmpList->next;
        } while (tmpList != head);
    }
    else
    {
        printf("Got an empty list! Nothing to print\n");
    }
}
