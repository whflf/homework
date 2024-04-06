#include <stdlib.h>
#include <string.h>

#include "tests.h"
#include "sort.h"
#include "errors.h"

#define ARRAY_SIZE 6

static bool test1(void)
{
    int array[6] = { 2, -9, 5, -7, 1, -4 };
    if (sortArray(array, 6) != ok)
    {
        return false;
    }

    const int sortedArray[6] = { -9, -7, -4, 1, 2, 5 };
    return memcmp(sortedArray, array, 6) == 0;
}

static bool test2(void)
{
    int array[6] = { 1, 2, 3, 4, 5, 6 };
    if (sortArray(array, 6) != ok)
    {
        return false;
    }

    const int sortedArray[6] = { 1, 2, 3, 4, 5, 6 };
    return memcmp(sortedArray, array, 6) == 0;
}

bool passTests(void)
{
    return test1() && test2();
}
