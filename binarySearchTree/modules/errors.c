#include <stdio.h>

#include "errors.h"

static char* getErrorMessage(const ErrorCode errorCode)
{
    switch (errorCode)
    {
    case outOfMemory:
        return "~ Memory allocation has failed. Exiting";
    case testsFailed:
        return "~ Tests failed.";
    default:
        return "Unknown error.";
    }
}

ErrorCode printErrorMessage(const ErrorCode errorCode)
{
    printf("[E] %s\n", getErrorMessage(errorCode));
    return errorCode;
}
