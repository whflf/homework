#pragma once

typedef enum
{
    ok,
    stackIsEmpty,
    outOfMemory,
    divisionByZero,
    badInput,
    testsFailed
} ErrorCode;

char* getErrorMessage(const ErrorCode errorCode);
