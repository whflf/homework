#pragma once

typedef enum ErrorCode
{
    ok,
    stackIsEmpty,
    outOfMemory,
    divisionByZero,
    badInput,
    testsFailed
} ErrorCode;

char* getErrorMessage(const ErrorCode errorCode);
