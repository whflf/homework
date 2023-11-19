#pragma once

typedef enum ErrorCode
{
    ok,
    stackIsEmpty,
    queueIsEmpty,
    outOfMemory,
    testsFailed
} ErrorCode;
