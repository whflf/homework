#include "errors.h"

char* getErrorMessage(const ErrorCode errorCode)
{
    switch (errorCode)
    {
    case stackIsEmpty:
        return "Stack is empty.";
        break;
    case outOfMemory:
        return "Memory allocation has failed.";
        break;
    case testsFailed:
        return "~ Tests failed.";
        break;
    }
    return "Unknown error.";
}
