#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>

#include "dialogue.h"

#define TEXT_BAD_INPUT "Bad input\n"

#define DYNAMIC_STRING_MIN_ALLOCATION_SIZE 16

typedef enum menuOptions 
{
    exitProgram,
    addValueToDictionary,
    getValueByKeyFromDictionary,
    checkForKeyInDictionary,
    deleteKeyFromDictionary,

    menuOptionsCount
} MenuOption;

static char* getString(void)
{
    size_t allocSize = DYNAMIC_STRING_MIN_ALLOCATION_SIZE, stringSize = 0;

    char* string = (char*)malloc(sizeof(char) * allocSize);
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
    while (getchar() != '\n');
}

static ErrorCode choiceAddValueToDictionary(Node** const root, const char* const inputKey)
{
    printf("Enter the value: ");

    char* inputValue = getString();
    if (inputValue == NULL)
    {
        return outOfMemory;
    }

    *root = insert(*root, inputKey, inputValue);
    const ErrorCode errorCode = *root != NULL ? ok : outOfMemory;
    if (*root != NULL)
    {
        printf("Value \"%s\" was added to the dictionary with key \"%s\".\n", inputValue, inputKey);
    }

    free(inputValue);
    return errorCode;
}

static void choiceGetValueByKeyFromDictionary(Node** const root, const char* const inputKey)
{
    const char* const foundValue = value(*root, inputKey);

    if (foundValue == NULL)
    {
        printf("Nothing was found for key \"%s\".\n", inputKey);
    }
    else
    {
        printf("The value for key \"%s\" is \"%s\".\n", inputKey, foundValue);
    }
}

static void choiceDeleteKeyFromDictionary(Node** const root, const char* const inputKey)
{
    if (isInDictionary(*root, inputKey))
    {
        *root = deleteNode(root, inputKey);
        printf("Key \"%s\" was successfully deleted from the dictionary.\n", inputKey);
    }
    else
    {
        printf("Key \"%s\" is not in the dictionary.\n", inputKey);
    }
}

static bool getKeyInput(char** const keyInput)
{
    printf("Enter the key: ");

    *keyInput = getString();
    if (keyInput == NULL)
    {
        return false;
    }

    return true;
}

ErrorCode programLoop(Node** const root)
{
    static const char* const menuOptionsNames[] = {
        [exitProgram] = "Exit",
        [addValueToDictionary] = "Add a value to the dictionary",
        [getValueByKeyFromDictionary] = "Get a value from the dictionary by key",
        [checkForKeyInDictionary] = "Check for a key in the dictionary",
        [deleteKeyFromDictionary] = "Delete a key from the dictionary"
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
        while (getchar() != '\n');

        system("cls");

        char* keyInput;

        const MenuOption coercedInput = input - '0';
        switch (coercedInput)
        {
        case exitProgram:
            printf("Goodbye!\n");
            wait();
            return ok;
        case addValueToDictionary:
        {
            if (!getKeyInput(&keyInput) || getKeyInput(&keyInput) && choiceAddValueToDictionary(root, keyInput) == outOfMemory)
            {
                return outOfMemory;
            }
            free(keyInput);
            break;
        }
        case getValueByKeyFromDictionary:
        {
            if (getKeyInput(&keyInput))
            {
                choiceGetValueByKeyFromDictionary(root, keyInput);
            }
            else
            {
                return outOfMemory;
            }
            free(keyInput);
            break;
        }
        case checkForKeyInDictionary:
        {
            if (getKeyInput(&keyInput))
            {
                printf(
                    "Key \"%s\" is %s the dictionary.\n", keyInput,
                    isInDictionary(*root, keyInput) ? "in" : "not in"
                );
            }
            else
            {
                return outOfMemory;
            }
            free(keyInput);
            break;
        }
        case deleteKeyFromDictionary:
        {
            if (getKeyInput(&keyInput))
            {
                choiceDeleteKeyFromDictionary(root, keyInput);
            }
            else
            {
                return outOfMemory;
            }
            free(keyInput);
            break;
        }
        default:
            printf(TEXT_BAD_INPUT);
        }

        wait();
    }
}
