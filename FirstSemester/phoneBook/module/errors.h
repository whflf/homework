#pragma once

#include <stdbool.h>

typedef enum
{
    ok,
    outOfMemory,
    fileError,
    entryLimitReached,
    testsFailed
} ErrorCode;

bool isFatalError(const ErrorCode errorCode);

ErrorCode printErrorMessage(const ErrorCode errorCode, const char* const ownMessage, const bool isFatal);
