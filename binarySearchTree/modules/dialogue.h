#pragma once

#include "errors.h"
#include "tree.h"

typedef enum menuOptions {
    exitProgram,
    addValueToDictionary,
    getValueByKeyFromDictionary,
    checkForKeyInDictionary,
    deleteKeyFromDictionary,

    menuOptionsCount
} MenuOption;

ErrorCode programLoop(Node** const root);
