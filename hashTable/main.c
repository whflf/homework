#include <stdio.h>

#include "module/errors.h"
#include "module/fileParsing.h"
#include "module/tests.h"

#define INPUT_FILE_NAME "input.txt"

ErrorCode main(void)
{
    if (!passTests())
    {
        return printErrorMessage(testsFailed);
    }

    ErrorCode error = ok;
    HashTable* frequencyTable = getFrequencyTableFromFile(INPUT_FILE_NAME, &error);
    if (error)
    {
        return printErrorMessage(error);
    }

    const float loadFactor = getLoadFactor(frequencyTable);
    printTable(frequencyTable);
    if (loadFactor > 0)
    {
        printf(
            "\nLoad factor: %.3f\nMax list length: %llu\nAverage list length: %llu\n",
            loadFactor,
            getMaxLength(frequencyTable),
            getAverageLength(frequencyTable)
        );
    }

    deleteHashTable(&frequencyTable);
    return ok;
}
