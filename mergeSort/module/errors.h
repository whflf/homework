#pragma once

typedef enum
{
    ok,
    outOfMemory,
    fileError,
    testsFailed,
    emptyInputFile
} ErrorCode;

ErrorCode printErrorMessage(const ErrorCode errorCode, const char* const ownMessage);
