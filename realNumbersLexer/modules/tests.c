#include <stdlib.h>

#include "tests.h"
#include "lexer.h"

#define TESTS_NUMBER 8

bool passTests(void)
{
    char* testStrings[] = { "359.158e-56", "6382730", "42x13", "", "123.32E+123+12", "123.32E-123", "123.23E123+12", "123.23E123" };
    bool testResults[] = { true, true, false, false, false, true, false, true };

    for (size_t i = 0; i < TESTS_NUMBER; ++i)
    {
        if (isNumber(testStrings[i]) != testResults[i])
        {
            return false;
        }
    }

    return true;
}
