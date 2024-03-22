#include "errors.h"

char* getErrorMessage(const ErrorCode errorCode)
{
    switch (errorCode)
    {
    case stackIsEmpty:
        return "Stack is empty.";
    case queueIsEmpty:
        return "Queue is empty.";
    case outOfMemory:
        return "~ Memory allocation has failed.";
    case testsFailed:
        return "~ Tests failed.";
    case wrongInput:
        return "Wrong input. Please enter a valid expression.";
    }
    return "Unknown error.";
}
