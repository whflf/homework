#pragma once

#include "list.h"
#include "errors.h"

typedef enum menuOptions {
    exitProgram,
    sortByName,
    sortByPhone,
    printUnsorted,

    menuOptionsCount
} MenuOption;

// main menu interface loop
ErrorCode programLoop(const List* const phoneBook);
