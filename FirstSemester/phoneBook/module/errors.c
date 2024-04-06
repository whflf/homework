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
    case entryLimitReached:
        return "Entry count is 100. Can't add more entries.";
    case testsFailed:
        return "Tests failed.";
    default:
        return "Unknown error.";
    }
}

bool isFatalError(const ErrorCode errorCode)
{
    return errorCode == outOfMemory || errorCode == testsFailed;
}

ErrorCode printErrorMessage(const ErrorCode errorCode, const char* const ownMessage, const bool isFatal)
{
    if (errorCode != ok)
    {
        printf(
            "[%s] %s\n",
            isFatal || isFatalError(errorCode) ? "F" : "E",
            getErrorMessage(errorCode)
        );
        if (ownMessage != NULL)
        {
            printf("~ %s\n", ownMessage);
        }
    }
    return errorCode;
}
