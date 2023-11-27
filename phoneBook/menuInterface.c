#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "phoneBook.h"
#include "errors.h"
#include "menuInterface.h"

static char* getString(void)
{
    size_t allocSize = ALLOC_SIZE, stringSize = 0;

    char* string = (char*)malloc(sizeof(char) * allocSize);
    if (string == NULL)
    {
        return NULL;
    }

    char character = '\0';
    while ((character = getchar()) != '\n')
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
    getchar();
}

void programLoop(Book* const book)
{
    system("cls");
    printf(MENU_TEXT);

    char input[5] = { 0 };
    fgets(input, 3, stdin);

    system("cls");
    switch (input[0])
    {
    case '0':
        printf("Goodbye!\n");
        wait();
        return;
    case '1':
    {
        printf("Enter the name: ");
        char* name = getString();
        if (name == NULL)
        {
            printf(OUT_OF_MEMORY_TEXT);
            return;
        }

        printf("Enter the phone: ");
        char* phone = getString();
        if (name == NULL)
        {
            printf(OUT_OF_MEMORY_TEXT);
            return;
        }

        switch (addEntry(book, name, phone))
        {
        case ok:
            printf("Entry \"%s\" added with phone number %s\n", name, phone);
            break;
        case outOfMemory:
            printf(OUT_OF_MEMORY_TEXT);
            break;
        case entryLimitReached:
            printf("Entry count is 100. Can't add more entries.\n");
            break;
        }

        free(name);
        free(phone);

        break;
    }
    case '2':
        printEntries(book);
        break;
    case '3':
    {
        printf("Enter the name to find phone number: ");
        char* const name = getString();
        if (name == NULL)
        {
            printf(OUT_OF_MEMORY_TEXT);
            return;
        }

        const int occurrenceIndex = findPhoneByName(book, name);

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
            printf(" No results for name \"%s\".\n", name);
        }

        free(name);

        break;
    }
    case '4':
    {
        printf("Enter the phone number to find name: ");
        char* phone = getString();
        if (phone == NULL)
        {
            printf(OUT_OF_MEMORY_TEXT);
            return;
        }

        const int occurrenceIndex = findNameByPhone(book, phone);

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
            printf(" No results for phone %s.\n", phone);
        }

        free(phone);

        break;
    }
    case '5':
        switch (saveContentToFile(book, BOOK_FILE_NAME))
        {
        case ok:
            printf("Unsaved changes have been successfully written to file.\n");
            break;
        case outOfMemory:
            printf(OUT_OF_MEMORY_TEXT);
            break;
        case fileError:
            printf("Failed to open file to write.\n");
            break;
        }
        break;
    }

    wait();

    programLoop(book);
}
