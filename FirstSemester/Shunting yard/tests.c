#include <stdlib.h>
#include <string.h>

#include "shuntingYard.h"
#include "tests.h"

#define TEST_EXPRESSION_LENGTH 11

static bool testOrdinaryCase(void)
{
    const char* const infixExpression = "(5*6-9*3)+8/4";
    const char* const postfixExpression = "5 6 * 9 3 * - 8 4 / +";

    char* const queueExpression = getPostfixExpression(infixExpression);
    if (queueExpression == NULL)
    {
        return false;
    }

    const bool result = memcmp(postfixExpression, queueExpression, TEST_EXPRESSION_LENGTH) == 0;

    free(queueExpression);
    return result;
}

static bool testSpaceCase(void)
{
    const char* const infixExpression = "9 / (6 - 7) * 2 * (1 + 1)";
    const char* const postfixExpression = "9 6 7 - / 2 * 1 1 + *";

    char* const queueExpression = getPostfixExpression(infixExpression);
    if (queueExpression == NULL)
    {
        return false;
    }

    const bool result = memcmp(postfixExpression, queueExpression, TEST_EXPRESSION_LENGTH) == 0;

    free(queueExpression);
    return result;
}

static bool testIncorrectCase(void)
{
    const char* const infixExpression = "- 2";
    return getPostfixExpression(infixExpression) == NULL;
}

bool passTests(void)
{
    return testOrdinaryCase() && testSpaceCase() && testIncorrectCase();
}
