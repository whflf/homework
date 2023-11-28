#include <stdio.h>
#include <stdlib.h>

#include "include/tree.h"
#include "include/errors.h"
#include "dialogue.h"

#define MENU_TEXT "Enter an operation code to continue:\n\
  0 - Exit\n\
  1 - Add a value to the dictionary\n\
  2 - Get a value from the dictionary by key\n\
  3 - Check for a key in the dictionary\n\
  4 - Delete a key from the dictionary\n\
> "
#define OUT_OF_MEMORY_TEXT "Failed to allocate memory. Exiting\n"

#define DYNAMIC_STRING_MIN_ALLOCATION_SIZE 16

static char* getString(void)
{
    size_t allocSize = DYNAMIC_STRING_MIN_ALLOCATION_SIZE, stringSize = 0;

    char* string = malloc(sizeof(char) * allocSize);
    if (string == NULL)
    {
        return NULL;
    }

    char character;
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

void programLoop(Node** root)
{
    system("cls");
    printf(MENU_TEXT);

    char input[5] = { 0 };

    fgets(input, 3, stdin);

    switch (input[0])
    {
    case '0':
        return;
    default:
        if (input[0] < '1' || input[0] > '4')
        {
            break;
        }

        printf("Enter the key: ");
        int inputKey = 0;

        if (scanf("%d", &inputKey))
        {
            switch (input[0])
            {
            case '1':
                printf("Enter the value: ");
                getchar();

                char* const inputValue = getString();
                if (inputValue == NULL)
                {
                    printf(errorMessages[outOfMemory]);
                    return;
                }

                ErrorCode errorCode = insert(root, inputKey, inputValue);
                if (errorCode == outOfMemory)
                {
                    printf(errorMessages[outOfMemory]);
                    return;
                }

                printf("Value \"%s\" was added to the dictionary with key %d.\n", inputValue, inputKey);
                break;

            case '2':;
                char* const foundValue = value(*root, inputKey);

                if (foundValue == NULL)
                {
                    printf("Nothing was found for key %d.\n", inputKey);
                }
                else
                {
                    printf("The value for key %d is \"%s\".\n", inputKey, foundValue);
                }

                getchar();
                break;
            case '3':
                if (isInDictionary(*root, inputKey))
                {
                    printf("Key %d is in the dictionary.\n", inputKey);
                }
                else
                {
                    printf("Key %d is not in the dictionary.\n", inputKey);
                }

                getchar();
                break;
            case '4':
                if (isInDictionary(*root, inputKey))
                {
                    deleteNode(root, inputKey);
                    printf("Key %d was successfully deleted from the dictionary.\n", inputKey);
                }
                else
                {
                    printf("Key %d is not in the dictionary.\n", inputKey);
                }

                getchar();
                break;
            }
        }
        else
        {
            printf("Wrong input. Please enter an integer and nothing else.\n");
        }
        break;
    }

    wait();

    programLoop(root);
}
