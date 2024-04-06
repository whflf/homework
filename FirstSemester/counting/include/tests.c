#include "counting.h"
#include "tests.h"

static bool testCalculateLastSoldierPosition(const size_t n, const size_t m, const size_t expectedResult)
{
    ErrorCode error;
    return calculateLastSoldierPosition(n, m, &error) == expectedResult && error == ok;
}

bool passTests(void)
{
    return
        testCalculateLastSoldierPosition(41, 3, 31) &&
        testCalculateLastSoldierPosition(100, 1, 100) &&
        testCalculateLastSoldierPosition(10, 3, 4);
}
