#pragma once

typedef enum
{
    ok,
    outOfMemory,
    fileError
} ErrorCode;

// gets text without same characters placing nearby
char* getText(const char* const filename);
