#pragma once

typedef enum
{
    ok,
    outOfMemory,
    fileError,
    entryLimitReached,
    testsFailed
} ErrorCode;
