#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "include/list.h"
#include "dialogue.h"

#define TEXT_BAD_INPUT "Bad input\n"

static void wait(void)
{
    printf("\nPress enter to continue...");
    getchar();
}

ErrorCode programLoop(List** head)
{
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
                printf("Enter the value: ");
                int value;
                char forNewLine;
                if (scanf("%d%c", &value, &forNewLine))
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
                    printf("Wrong input. Please enter an integer and nothing else");
                }
                break;
            }
        }

        wait();
    }
}

