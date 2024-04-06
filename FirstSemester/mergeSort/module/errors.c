#include <stdio.h>
#include "errors.h"

static char* getErrorMessage(const ErrorCode errorCode)
{
    switch (errorCode)
    {
    case outOfMemory:
        return "Failed to allocate memory.";
    case fileError:
        return "File error occurred.";
    case testsFailed:
        return "Tests failed.";
    case emptyInputFile:
        return "Empty input file.";
    default:
        return "Unknown error.";
    }
}

ErrorCode printErrorMessage(const ErrorCode errorCode, const char* const ownMessage)
{
    if (errorCode != ok)
    {
        printf("[E] %s\n", getErrorMessage(errorCode));
        if (ownMessage != NULL)
        {
            printf("~ %s\n", ownMessage);
        }
    }
    return errorCode;
}
