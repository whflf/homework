#pragma once

typedef enum
{
    ok,
    outOfMemory,
    testsFailed,
} ErrorCode;

char* getErrorMessage(const ErrorCode errorCode);
