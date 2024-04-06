#pragma once

#include "include/errors.h"
#include "include/list.h"

typedef enum menuOptions {
    exitProgram,
    addValueToList,
    removeValueFromList,
    showList,

    menuOptionsCount
} MenuOption;

ErrorCode programLoop(List** const head);

