#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "include/errors.h"
#include "include/list.h"
#include "tests.h"

static List* testList(void)
{
    List* list = NULL;

    const ErrorCode error = sortingInsert(&list, 4);
    const ErrorCode error2 = sortingInsert(&list, 2);
    const ErrorCode error3 = sortingInsert(&list, 70);
    if (error != ok || error2 != ok || error3 != ok)
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

    if (sortingInsert(&list, 3) != ok)
    {
        deleteList(&list);
        return false;
    }

    int* const vector = writeListToArray(list);
    if (vector == NULL)
    {
        deleteList(&list);
        return false;
    }

    const int correctVector[] = { 2, 3, 4, 70 };

    const bool result = memcmp(vector, correctVector, getLength(list) * sizeof(int)) == 0;

    free(vector);
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

    int* const vector = writeListToArray(list);
    if (vector == NULL)
    {
        deleteList(&list);
        return false;
    }

    const int correctVector[] = { 4, 70 };

    const bool result = memcmp(vector, correctVector, getLength(list) * sizeof(int)) == 0;

    free(vector);
    deleteList(&list);

    return result;
}

bool passTests(void)
{
    return testInserting() && testDeleting();
}
