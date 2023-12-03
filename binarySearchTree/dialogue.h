#pragma once

#include "include/errors.h"
#include "include/tree.h"

typedef enum menuOptions {
    exitProgram,
    addValueToDictionary,
    getValueByKeyFromDictionary,
    checkForKeyInDictionary,
    deleteKeyFromDictionary,

    menuOptionsCount
} MenuOption;

ErrorCode programLoop(Node** const root);
