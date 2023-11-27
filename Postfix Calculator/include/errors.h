#pragma once

typedef enum ErrorCode
{
    ok,
    stackIsEmpty,
    outOfMemory,
    divisionByZero,
    testsFailed
} ErrorCode;

static const char* const errorMessages[] = {
    [ok] = "",
    [stackIsEmpty] = "Stack is empty.\n",
    [outOfMemory] = "Memory allocation has failed.\n",
    [divisionByZero] = "Division by zero is forbidden. Please enter a valid expression.\n",
    [testsFailed] = "~ Tests failed.\n"
};