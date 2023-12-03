#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dialogue.h"

#define TEXT_BAD_INPUT "Bad input\n"

static void wait(void)
{
    printf("\nPress enter to continue...");
    while (getchar() != '\n');
}

ErrorCode programLoop(List** const head)
{
    const char* const menuOptionsNames[] = {
        [exitProgram] = "Exit",
        [addValueToList] = "Add a value to the sorted list",
        [removeValueFromList] = "Remove a value from the list",
        [showList] = "Print the list"
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
            const MenuOption coercedInput = input - 0x30;
            switch (coercedInput)
            {
            case exitProgram:
                printf("Goodbye!\n");
                wait();
                return ok;
            case showList:
                printList(*head);
                break;
            case addValueToList:
            case removeValueFromList:
            {
                int value;
                char forNewLine;
                printf("Enter the value: ");
                const int filledFields = scanf("%d%c", &value, &forNewLine);

                system("cls");

                if (filledFields == 2 && forNewLine == '\n')
                {
                    if (coercedInput == addValueToList && sortingInsert(head, value) == outOfMemory)
                    {
                        return outOfMemory;
                    }
                    else if (coercedInput == removeValueFromList)
                    {
                        exclude(head, value);
                    }
                }
                else
                {
                    while (getchar() != '\n');
                    printf("Wrong input. Please enter an integer and nothing else\n");
                }
                break;
            }
            default:
                printf(TEXT_BAD_INPUT);
            }
        }

        wait();
    }
}
