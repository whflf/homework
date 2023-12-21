#pragma once

typedef enum
{
    ok,
    outOfMemory,
    testsFailed
} ErrorCode;

ErrorCode printErrorMessage(const ErrorCode errorCode);
