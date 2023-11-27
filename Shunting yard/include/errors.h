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

static const char* const errorMessages[] = {
    [ok] = "",
    [stackIsEmpty] = "Stack is empty.\n",
    [queueIsEmpty] = "Queue is empty.\n",
    [outOfMemory] = "~ Memory allocation has failed.\n",
    [testsFailed] = "~ Tests failed.\n",
    [wrongInput] = "Wrong input. Please enter a valid expression.\n"
};
