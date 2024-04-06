#pragma once

typedef enum
{
    ok,
    outOfMemory,
    fileError,
    testsFailed
} ErrorCode;

ErrorCode printErrorMessage(const ErrorCode errorCode);
