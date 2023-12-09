#pragma once

typedef enum
{
    ok,
    outOfMemory,
    fileOpeningError,
    fileParsingError,
    testsFailed
} ErrorCode;

ErrorCode printErrorMessage(const ErrorCode errorCode);
