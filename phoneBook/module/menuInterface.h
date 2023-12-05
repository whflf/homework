#pragma once

#include "phoneBook.h"
#include "errors.h"

typedef enum menuOptions
{
    optExitProgram,
    optAddEntry,
    optPrintEntries,
    optFindPhoneByName,
    optFindNameByPhone,
    optSaveToFile,

    menuOptionsCount
} MenuOption;

ErrorCode programLoop(Book* const book);
