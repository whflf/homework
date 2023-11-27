#include <stdlib.h>
#include <stdbool.h>

#include "include/errors.h"
#include "include/list.h"

static List* testList(void)
{
    List* list = NULL;

    ErrorCode errorFirst = sortingInsert(&list, 4);
    ErrorCode errorSecond = sortingInsert(&list, 2);
    ErrorCode errorThird = sortingInsert(&list, 7);

    if (errorFirst != ok || errorSecond != ok || errorThird != ok)
    {
        return NULL;
    }

    return list;
}

static bool testInserting(void)
{
    List* list = testList();
    ErrorCode error = sortingInsert(&list, 3);

    if (error != ok)
    {
        return false;
    }

    char* string[8] = writeListToString(list);
    bool result = string == "2 3 4 7";

    deleteList(&list);
    return result;
}

static bool testDeleting(void)
{
    List* list = testList();
    exclude(&list, 2);

    char* string[8] = writeListToString(list);
    bool result = string == "4 7";

    deleteList(&list);
    return result;
}

bool passTests(void)
{
    return testInserting() && testDeleting();
}
