#include <stdlib.h>

#include "tests.h"
#include "lexer.h"

static bool testFloatNumber(void)
{
    return isNumber("359.158e-56");
}

static bool testIntegerNumber(void)
{
    return isNumber("6382730");
}

static bool testNotNumber(void)
{
    return !isNumber("42x13");
}

static bool testEmptyString(void)
{
    return !isNumber("");
}

bool passTests(void)
{
    return testFloatNumber() && testIntegerNumber() && testNotNumber() && testEmptyString();
}
