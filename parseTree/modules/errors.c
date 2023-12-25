#include <stdio.h>

#include "errors.h"

static char* getErrorMessage(const ErrorCode errorCode)
{
    switch (errorCode)
    {
    case outOfMemory:
        return "Memory allocation has failed. Exiting";
    case testsFailed:
        return "Tests failed.";
    case fileOpeningError:
        return "An error occurred while opening file.";
    case fileParsingError:
        return "An error occurred while parsing file contents.";
    case divisionByZero:
        return "Division by zero occurred in expression.";
    default:
        return "Unknown error.";
    }
}

ErrorCode printErrorMessage(const ErrorCode errorCode)
{
    printf("[E] %s\n", getErrorMessage(errorCode));
    return errorCode;
}
