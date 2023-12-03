#include <stdio.h>
#include <stdlib.h>

#include "dialogue.h"
#include "tests.h"

#define ERROR_FORMAT_STRING "[E] %s\n"

int main(void)
{
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
