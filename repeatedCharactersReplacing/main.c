#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "fileParsing.h"

#define FIRST_TEST_FILENAME "test1.txt"
#define SECOND_TEST_FILENAME "test2.txt"
#define THIRD_TEST_FILENAME "test3.txt"

#define INPUT_FILE_NAME "input.txt"

#define OK 0
#define TESTS_FAILED 1

bool test1(void)
{
    ErrorCode error = ok;
    char* const text = getText(FIRST_TEST_FILENAME, &error);
    if (error)
    {
        return false;
    }

    char correctString[] = "123\n456";

    const bool result = strcmp(text, correctString) == 0;
    free(text);

    return result;
}

bool test2(void)
{
    ErrorCode error = ok;
    char* const text = getText(SECOND_TEST_FILENAME, &error);
    if (error)
    {
        return false;
    }

    char correctString[] = "123456";

    const bool result = strcmp(text, correctString) == 0;
    free(text);

    return result;
}

bool test3(void)
{
    ErrorCode error = ok;
    char* const text = getText(THIRD_TEST_FILENAME, &error);
    if (error)
    {
        return false;
    }

    char correctString[] = "\0";

    const bool result = strcmp(text, correctString) == 0;
    free(text);

    return result;
}

int main(void)
{
    if (!test1() || !test2() || !test3())
    {
        printf("~ Tests failed.\n");
        return TESTS_FAILED;
    }

    ErrorCode error = ok;
    char* const text = getText(INPUT_FILE_NAME, &error);
    switch (error)
    {
    case fileError:
        printf("~ File is not found.\n");
        break;
    case outOfMemory:
        printf("~ Couldn't allocate memory.\n");
        break;
    case ok:
        printf("File content without repeating characters: %s\n", text);
        break;
    default:
        break;
    }

    return error;
}
