#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "include/counting.h"
#include "include/tests.h"

static bool processSizeInput(const char* const prompt, size_t* const intPtr)
{
    printf(prompt);
    if (scanf_s("%zu", intPtr) == 0)
    {
        printf("Wrong input. Enter a positive integer.\n");
        return false;
    }

    if (*intPtr == 0 || *intPtr > LLONG_MAX)
    {
        printf("Input can't be zero or negative.\n");
        return false;
    }

    while (getchar() != '\n');

    return true;
}

int main(void)
{
    if (!passTests())
    {
        printf("Tests failed.\n");
        return testsFailed;
    }

    size_t n, m;
    if (!processSizeInput("> n (number of soldiers) = ", &n) || !processSizeInput("> m (destroy step) = ", &m))
    {
        return wrongInput;
    }

    ErrorCode errorCode = ok;
    const size_t lastSoldierPosition = calculateLastSoldierPosition(n, m, &errorCode);
    if (errorCode != ok)
    {
        printf("Error in calculateLastSoldierPosition(). Code: %d.\n", errorCode);
        return errorCode;
    }

    printf("\nLast soldier position: %zu\n", lastSoldierPosition);

    return ok;
}
