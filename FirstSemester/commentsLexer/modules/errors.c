#include <stdio.h>

#include "errors.h"

static char* getErrorMessage(const ErrorCode errorCode)
{
    switch (errorCode)
    {
    case ok:
        return "";
    case outOfMemory:
        return "~ Memory allocation has failed. Exiting";
    case fileError:
        return "File error occurred.";
    case testsFailed:
        return "~ Tests failed.";
    default:
        return "Unknown error.";
    }
}

ErrorCode printErrorMessage(const ErrorCode errorCode)
{
    printf("%s %s\n", errorCode == ok ? "" : "[E]", getErrorMessage(errorCode));
    return errorCode;
}
