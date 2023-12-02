#include <stdlib.h>
#include <stdbool.h>

#include "include/errors.h"
#include "include/list.h"

static List* testList(void)
{
    List* list = NULL;

    ErrorCode errorFirst = sortingInsert(&list, 4);
    ErrorCode errorSecond = sortingInsert(&list, 2);
    ErrorCode errorThird = sortingInsert(&list, 70);

    if (errorFirst != ok || errorSecond != ok || errorThird != ok)
    {
        return NULL;
    }

    return list;
}

static bool testInserting(void)
{
    List* list = testList();
    if (list == NULL)
    {
        return false;
    }

    ErrorCode error = sortingInsert(&list, 3);

    if (error != ok)
    {
        return false;
    }

    int* vector = writeListToArray(list);
    int* correctVector[] = {2, 3, 4, 70};
    bool result = memcmp(vector, correctVector, getLength(list)) == 0;

    deleteList(&list);
    return result;
}

static bool testDeleting(void)
{
    List* list = testList();
    if (list == NULL)
    {
        return false;
    }

    exclude(&list, 2);

    int* vector = writeListToArray(list);
    int* correctVector[] = { 4, 70 };
    bool result = memcmp(vector, correctVector, getLength(list)) == 0;

    deleteList(&list);
    return result;
}

bool passTests(void)
{
    return testInserting() && testDeleting();
}
