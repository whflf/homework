#include <stdio.h>
#include <stdlib.h>

#include "include/list.h"
#include "include/errors.h"
#include "dialogue.h"

#define MENU_TEXT "Enter an operation code to continue:\n\
  0 - Exit\n\
  1 - Add a value to the sorted list\n\
  2 - Remove a value from the list\n\
  3 - Print the list\n\
> "

static void wait(void)
{
    printf("\nPress enter to continue...");
    getchar();
}

void programLoop(List** head)
{
    system("cls");
    printf(MENU_TEXT);

    char input[5] = { 0 };

    fgets(input, 3, stdin);

    switch (input[0])
    {
    case '0':
        printf("Goodbye!\n");
        wait();
        return;
    case '3':
        printList(*head);
        break;
    default:
        printf("Enter the value: ");
        int value = 0;
        if (scanf("%d", &value))
        {
            switch (input[0])
            {
            case '1':
                if (sortingInsert(head, value) == outOfMemory)
                {
                    printf(errorMessages[outOfMemory]);
                    return;
                }
                getchar();
                break;
            case '2':
                exclude(head, value);
                getchar();
                break;
            }
        }
        else
        {
            printf("Wrong input. Please enter an integer and nothing else");
        }
        break;
    }

    wait();

    programLoop(head);
}
