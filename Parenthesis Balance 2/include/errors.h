#pragma once

typedef enum ErrorCode
{
    ok,
    stackIsEmpty,
    outOfMemory,
    testsFailed
} ErrorCode;

static const char* const errorMessages[] = {
    [ok] = "",
    [stackIsEmpty] = "Stack is empty.\n",
    [outOfMemory] = "Memory allocation has failed.\n",
    [testsFailed] = "~ Tests failed.\n"
};
