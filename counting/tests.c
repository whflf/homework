#include "include/circularList.h"
#include "tests.h"

static bool testCorrectCase(void)
{
    List* const soldiers = calculateLastSoldierPosition(41, 3);
    const bool result = getElementAtPosition(soldiers, 0)->value == 31;
    deleteList(soldiers);
    return result;
}

static bool testBoundaryCase(void)
{
    List* const soldiers = calculateLastSoldierPosition(100, 1);
    const bool result = getElementAtPosition(soldiers, 0)->value == 100;
    deleteList(soldiers);
    return result;
}

bool passTests(void)
{
    return testCorrectCase() && testBoundaryCase();
}
