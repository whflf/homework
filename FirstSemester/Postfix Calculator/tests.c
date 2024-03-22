#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "include/stack.h"
#include "include/errors.h"
#include "calculator.h"
#include "tests.h"

static bool testCorrectCase1(void)
{
    char expression[] = "4 3 + 9 8 - / 5 *";
    ErrorCode errorCode;
    return getResult(expression, &errorCode) == 35;
}

static bool testCorrectCase2(void)
{
    char expression[] = "25*69+*";
    ErrorCode errorCode;
    return getResult(expression, &errorCode) == 150;
}

static bool testIncorrectCase(void)
{
    char expression[] = "2 - *";
    ErrorCode errorCode;
    getResult(expression, &errorCode);
    return errorCode == stackIsEmpty;
}

static bool testIncorrectCase2(void)
{
    char expression[] = "6 0 /";
    ErrorCode errorCode;
    getResult(expression, &errorCode);
    return errorCode == divisionByZero;
}

bool passTests(void)
{
    return testCorrectCase1() && testCorrectCase2() && testIncorrectCase() && testIncorrectCase2();
}
