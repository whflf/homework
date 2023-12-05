#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

#include "phoneBook.h"
#include "errors.h"
#include "menuInterface.h"

#define ALLOC_SIZE 16
#define TEXT_BAD_INPUT "Bad input.\n"

static char* getString(FILE* const file, const char breakingChar)
{
    size_t allocSize = ALLOC_SIZE, stringSize = 0;

    char* string = (char*)malloc(sizeof(char) * allocSize);
    if (string == NULL)
    {
        return NULL;
    }

    char character;
    while ((character = getc(file)) != breakingChar)
    {
        if (stringSize >= allocSize - 1)
        {
            allocSize *= 2;
            string = realloc(string, allocSize * sizeof(char));
            if (string == NULL)
            {
                return NULL;
            }
        }
        string[stringSize] = character;
        ++stringSize;
    }

    string[stringSize] = '\0';

    return string;
}

static void wait(void)
{
    printf("\nPress enter to continue...");
    while (getchar() != '\n');
}

static ErrorCode choiceAddEntry(Book* const book)
{
    printf("Enter the name: ");
    char* const name = getString(stdin, '\n');
    if (name == NULL)
    {
        return printErrorMessage(outOfMemory, "While allocating memory for name in choiceAddEntry()", true);
    }

    printf("Enter the phone: ");
    char* const phone = getString(stdin, '\n');
    if (phone == NULL)
    {
        free(name);
        return printErrorMessage(outOfMemory, "While allocating memory for phone in choiceAddEntry()", true);
    }

    const ErrorCode errorCode = printErrorMessage(addEntry(book, name, phone), NULL, false);
    if (errorCode == ok)
    {
        printf("Entry \"%s\" added with phone number %s\n", name, phone);
    }

    free(name);
    free(phone);

    return errorCode;
}

static ErrorCode choiceFindEntry(const Book* const book, const bool toFindPhone)
{
    const char* const a = "name";
    const char* const b = "phone number";

    printf("Enter %s to find %s: ", toFindPhone ? a : b, toFindPhone ? b : a);
    char* string = getString(stdin, '\n');
    if (string == NULL)
    {
        return printErrorMessage(outOfMemory, "While allocating memory for name in choiceFindEntry()", true);
    }

    const int occurrenceIndex = findEntry(book, string, toFindPhone);

    printf("Result:\n");
    if (occurrenceIndex >= 0)
    {
        printf(
            " %d: %s - %s\n",
            occurrenceIndex + 1,
            book->entries[occurrenceIndex].name,
            book->entries[occurrenceIndex].phone
        );
    }
    else
    {
        printf(" No results for %s \"%s\".\n", toFindPhone ? a : b, string);
    }

    free(string);
    return ok;
}

ErrorCode programLoop(Book* const book)
{
    const char* const menuOptionsNames[] = {
        [optExitProgram] = "Exit",
        [optAddEntry] = "Add an entry",
        [optPrintEntries] = "Print existing entries",
        [optFindPhoneByName] = "Find phone number by name",
        [optFindNameByPhone] = "Find name by phone number",
        [optSaveToFile] = "Save everything to database file"
    };

    while (true)
    {
        system("cls");

        printf("Enter an operation code to continue:\n");
        for (size_t i = 0; i < menuOptionsCount; ++i)
        {
            printf("  %zu - %s\n", i, menuOptionsNames[i]);
        }
        printf("> ");

        const char input = getchar();
        bool badInput = input == '\n';
        if (!badInput)
        {
            while (getchar() != '\n')
            {
                badInput = true;
            }
        }

        system("cls");

        if (badInput)
        {
            printf(TEXT_BAD_INPUT);
        }
        else
        {
            ErrorCode errorCode = ok;

            const MenuOption coercedInput = input - 0x30;
            switch (coercedInput)
            {
            case optExitProgram:
                printf("Goodbye!\n");
                wait();
                return ok;
            case optAddEntry:
                errorCode = choiceAddEntry(book);
                break;
            case optPrintEntries:
                printEntries(book);
                break;
            case optFindPhoneByName:
                errorCode = choiceFindEntry(book, true);
                break;
            case optFindNameByPhone:
                errorCode = choiceFindEntry(book, false);
                break;
            case optSaveToFile:
                if ((errorCode = saveContentToFile(book, BOOK_FILE_NAME)) == ok)
                {
                    printf("Unsaved changes have been successfully written to file.\n");
                }
                break;
            default:
                printf(TEXT_BAD_INPUT);
            }

            if (isFatalError(errorCode))
            {
                return errorCode;
            }
        }

        wait();
    }
}
