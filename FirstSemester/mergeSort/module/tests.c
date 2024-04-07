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

    const ListValue expectedNamesSortByName[] = { "A", "B", "Brother", "C", "D", "Dylan", "E", "Eva", "F", "G", "H", "I", "J", "Mom" };
    const ListValue expectedPhonesSortByName[] = { "9", "8", "451", "7", "6", "982", "5", "720", "4", "3", "2", "1", "0", "908" };
    const ListValue expectedNamesSortByPhone[] = { "J", "I", "H", "G", "F", "Brother", "E", "D", "C", "Eva", "B", "A", "Mom", "Dylan" };
    const ListValue expectedPhonesSortByPhone[] = { "0", "1", "2", "3", "4", "451", "5", "6", "7", "720", "8", "9", "908", "982"};

    const size_t size = countof(expectedNamesSortByName);

    const bool result =
        sortByOptionTest(phoneBook, byName, expectedNamesSortByName, expectedPhonesSortByName, size) &&
        sortByOptionTest(phoneBook, byPhone, expectedNamesSortByPhone, expectedPhonesSortByPhone, size);

    deleteList(&phoneBook);
    free(content);

    return result;
}
