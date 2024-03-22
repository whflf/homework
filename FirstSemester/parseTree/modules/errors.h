#pragma once

typedef enum
{
    ok,
    outOfMemory,
    fileOpeningError,
    fileParsingError,
    testsFailed,
    divisionByZero
} ErrorCode;

ErrorCode printErrorMessage(const ErrorCode errorCode);
