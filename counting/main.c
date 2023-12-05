#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "include/circularList.h"
#include "tests.h"

#define TEXT_WRONG_INPUT_SCANF "Wrong input. Enter a positive integer.\n"

List* calculateLastSoldierPosition(const int n, const int m)
{
    List* soldiers = NULL;

    if (m == 1)
    {
        if (insertElement(&soldiers, n) != ok)
        {
            return NULL;
        }
    }
    else
    {
        for (size_t i = 1; i <= n; ++i) 
        {
            if (insertElement(&soldiers, i) != ok)
            {
                return NULL;
            }
        }

        int steps = 0;

        const List* element = getElementAtPosition(soldiers, 0);
        while (element != element->next)
        {
            ++steps;
            if ((steps + 1) % m == 0) 
            {
                removeElement(&soldiers, element->next);
                ++steps;
            }
            element = element->next;
        }
    }

    return soldiers;
}

static bool processIntInput(const char* const prompt, int* const intPtr)
{
    printf(prompt);
    if (scanf_s("%d", intPtr) == 0)
    {
        printf(TEXT_WRONG_INPUT_SCANF);
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

    int n, m;
    if (!processIntInput("> n (number of soldiers) = ", &n) || !processIntInput("> m (destroy step) = ", &m))
    {
        return wrongInput;
    }

    if (n <= 0 || m <= 0)
    {
        printf("n or m can't be zero or negative.\n");
        return wrongInput;
    }

    List* const soldiers = calculateLastSoldierPosition(n, m);
    if (!soldiers)
    {
        printf("Couldn't create soldiers list (out of memory).\n");
        return outOfMemory;
    }

    printf("Last soldier position: ");
    printList(soldiers);

    deleteList(soldiers);

    return ok;
}
