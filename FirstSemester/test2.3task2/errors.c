#include <stdio.h>

#include "errors.h"

static char* getErrorMessage(const ErrorCode errorCode)
{
    switch (errorCode)
    {
    case ok:
        return "OK";
    case outOfMemory:
        return "~ Memory allocation has failed. Exiting";
    case testsFailed:
        return "~ Tests failed.";
    default:
        return "~ Unknown error.";
    }
}

ErrorCode printErrorMessage(const ErrorCode errorCode)
{
    printf("%s %s\n", errorCode == ok ? "" : "[E]", getErrorMessage(errorCode));
    return errorCode;
}
