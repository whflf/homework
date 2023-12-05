#pragma once

#include "phoneBook.h"
#include "errors.h"

typedef enum menuOptions
{
    optExitProgram = '0',
    optAddEntry,
    optPrintEntries,
    optFindPhoneByName,
    optFindNameByPhone,
    optSaveToFile,

    menuOptionsCount
} MenuOption;

ErrorCode programLoop(Book* const book);
