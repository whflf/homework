#include "errors.h"

char* getErrorMessage(const ErrorCode errorCode)
{
    switch (errorCode)
    {
    case stackIsEmpty:
        return "Stack is empty.";
    case outOfMemory:
        return "Memory allocation has failed.";
    case divisionByZero:
        return "Division by zero is forbidden. Please enter a valid expression.";
    case badInput:
        return "The expression isn't correct.";
    case testsFailed:
        return "~ Tests failed.";
    default:
        return "Unknown error.";
    }
}
