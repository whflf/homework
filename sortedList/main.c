#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dialogue.h"
#include "tests.h"

#define ERROR_FORMAT_STRING "[E] %s\n"

int main(int argc, char* argv[])
{
    if (argc > 1 && strcmp(argv[1], "run tests") == 0)
    {
        return passTests() ? 0 : 1;
    }

    if (!passTests())
    {
        printf(ERROR_FORMAT_STRING, getErrorMessage(testsFailed));
        return testsFailed;
    }

    List* myList = NULL;

    ErrorCode errorCode = programLoop(&myList);
    if (errorCode != ok)
    {
        printf(ERROR_FORMAT_STRING, getErrorMessage(errorCode));
    }

    deleteList(&myList);
    return errorCode;
}
