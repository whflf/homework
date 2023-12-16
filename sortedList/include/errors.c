#include "errors.h"

char* getErrorMessage(const ErrorCode errorCode)
{
    switch (errorCode)
    {
    case outOfMemory:
        return "~ Memory allocation has failed.";
    case testsFailed:
        return "~ Tests failed.";
    }
    return "Unknown error.";
}
