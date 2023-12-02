#pragma once

#include "include/errors.h"

typedef enum menuOptions {
    exitProgram,
    addValueToList,
    removeValueFromList,
    showList,

    menuOptionsCount
} MenuOption;

static const char* const menuOptionsNames[] = {
    [exitProgram] = "Exit",
    [addValueToList] = "Add a value to the sorted list",
    [removeValueFromList] = "Remove a value from the list",
    [showList] = "Print the list"
};

ErrorCode programLoop(List** head);

