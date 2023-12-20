#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "fileUtils.h"
#include "tests.h"
#include "list.h"

#define TEST_FILE "test.txt"

#define countof(array) sizeof(array) / sizeof(array[0])

static bool sortByOptionTest(
    List* phoneBook,
    const BookSortOption option,
    const ListValue* const expectedOrderedNames,
    const ListValue* const expectedOrderedPhones,
    const size_t expectedOrderedEntriesLength
)
{
    List* sortedBook = mergeSort(cloneList(phoneBook), option);

    for (size_t i = 0; i < expectedOrderedEntriesLength; ++i)
    {
        List* element = getElement(sortedBook, i);
        if (strcmp(element->name, expectedOrderedNames[i]) != 0 ||
            strcmp(element->phone, expectedOrderedPhones[i]) != 0)
        {
            deleteList(&sortedBook);
            return false;
        }
    }

    deleteList(&sortedBook);
    return true;
}

bool passTests(void)
{
    ErrorCode error = ok;

    char* content = NULL;
    size_t fileSize = 0;

    if ((error = readFile(TEST_FILE, &content, &fileSize)) != ok)
    {
        return false;
    }

    List* phoneBook = NULL;

    if ((error = deserializeBookContent(content, &phoneBook)) != ok)
    {
        deleteList(&phoneBook);
        free(content);
        return false;
    }

    const ListValue expectedNamesSortByName[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };
    const ListValue expectedPhonesSortByName[] = { "9", "8", "7", "6", "5", "4", "3", "2", "1", "0" };
    const ListValue expectedNamesSortByPhone[] = { "J", "I", "H", "G", "F", "E", "D", "C", "B", "A" };
    const ListValue expectedPhonesSortByPhone[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

    const size_t size = countof(expectedNamesSortByName);

    const bool result =
        sortByOptionTest(phoneBook, byName, expectedNamesSortByName, expectedPhonesSortByName, size) &&
        sortByOptionTest(phoneBook, byPhone, expectedNamesSortByPhone, expectedPhonesSortByPhone, size);

    deleteList(&phoneBook);
    free(content);

    return result;
}
