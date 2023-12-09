#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "fileUtils.h"
#include "tests.h"
#include "list.h"

#define TEST_FILE "test.txt"

static bool sortByOptionTest(
    const List* const phoneBook,
    const BookSortOption option,
    const char* const expectedName,
    const char* const expectedPhone
)
{
    const size_t bookSize = getSize(phoneBook);
    List* sortedBook = mergeSort(&phoneBook, 0, bookSize, option);
    
    List* firstElement = getElement(&sortedBook, 0);

    const bool result =
        strcmp(firstElement->name, expectedName) == 0 &&
        strcmp(firstElement->phone, expectedPhone) == 0;

    deleteList(&sortedBook);
    
    return result;
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

    const bool result =
        sortByOptionTest(phoneBook, byName, "A", "9") &&
        sortByOptionTest(phoneBook, byPhone, "J", "0");

    deleteList(&phoneBook);
    free(content);

    return result;
}
