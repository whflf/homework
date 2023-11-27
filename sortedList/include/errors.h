#pragma once

typedef enum
{
    ok,
    outOfMemory,
    testsFailed,
} ErrorCode;

static const char* const errorMessages[] = {
    [ok] = "",
    [outOfMemory] = "~ Memory allocation has failed.\n",
    [testsFailed] = "~ Tests failed.\n",
};
