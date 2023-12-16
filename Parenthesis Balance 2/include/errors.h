#pragma once

typedef enum ErrorCode
{
    ok,
    stackIsEmpty,
    outOfMemory,
    testsFailed
} ErrorCode;

char* getErrorMessage(const ErrorCode errorCode);
