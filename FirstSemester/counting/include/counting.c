#include "circularList.h"
#include "counting.h"

size_t calculateLastSoldierPosition(const size_t n, const size_t m, ErrorCode* const errorCode)
{
    *errorCode = ok;
    List* soldiers = NULL;

    if (m == 1)
    {
        return n;
    }
    else
    {
        for (size_t i = 1; i <= n; ++i)
        {
            if ((*errorCode = insertElement(&soldiers, i)) != ok)
            {
                deleteList(&soldiers);
                return 0;
            }
        }

        for (size_t steps = 0; soldiers != getNext(soldiers); ++steps)
        {
            if ((steps + 1) % m == 0)
            {
                removeElement(&soldiers, soldiers);
                ++steps;
            }
            soldiers = getNext(soldiers);
        }
    }

    const size_t result = getValue(soldiers);
    deleteList(&soldiers);
    return result;
}
