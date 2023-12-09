#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"
#include "menuInterface.h"
#include "errors.h"

#define TEXT_BAD_INPUT "Bad input\n"

static void wait(void)
{
    printf("\nPress enter to continue...");
    while (getchar() != '\n');
}

static ErrorCode sortBook(const List* const phoneBook, const BookSortOption sortOption)
{
    const size_t bookSize = getSize(phoneBook);
    List* sortedBook = mergeSort(&phoneBook, 0, bookSize, sortOption);
    if (sortedBook == NULL)
    {
        return printErrorMessage(outOfMemory, "mergeSort() result in sortBook() is NULL");
    }
    printList(sortedBook);
    deleteList(&sortedBook);
    return ok;
}

ErrorCode programLoop(const List* const phoneBook)
{
    const char* const menuOptionsNames[] = {
        [exitProgram] = "Exit",
        [sortByName] = "Sort by name",
        [sortByPhone] = "Sort by phone",
        [printUnsorted] = "Print unsorted"
    };

    while (true)
    {
        system("cls");

        printf("Select an option from list below to continue:\n");
        for (size_t i = 0; i < menuOptionsCount; ++i)
        {
            printf("  %zu - %s\n", i, menuOptionsNames[i]);
        }
        printf("> ");

        const char input = getchar();
        while (getchar() != '\n');

        system("cls");

        ErrorCode errorCode = ok;

        const MenuOption coercedInput = input - '0';
        switch (coercedInput)
        {
        case exitProgram:
            printf("Thanks for using the program!\n");
            wait();
            return ok;
        case sortByName:
            errorCode = sortBook(phoneBook, byName);
            break;
        case sortByPhone:
            errorCode = sortBook(phoneBook, byPhone);
            break;
        case printUnsorted:
            printList(phoneBook);
            break;
        default:
            printf(TEXT_BAD_INPUT);
            break;
        }

        if (errorCode != ok)
        {
            return errorCode;
        }

        wait();
    }
}
