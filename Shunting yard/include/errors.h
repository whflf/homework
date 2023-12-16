#pragma once

typedef enum ErrorCode
{
    ok,
    stackIsEmpty,
    queueIsEmpty,
    outOfMemory,
    testsFailed,
    wrongInput
} ErrorCode;

char* getErrorMessage(const ErrorCode errorCode);
