#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "include/queue.h"
#include "include/stack.h"
#include "tests.h"
#include "shuntingYard.h"

#define TEST_EXPRESSION_LENGTH 11

static bool testOrdinaryCase(void)
{
    const char* const infixExpression = "(5*6-9*3)+8/4";
    const char* const postfixExpression = "5 6 * 9 3 * - 8 4 / +";

    ErrorCode errorCode;
    char* queueExpression = getPostfixExpression(infixExpression, &errorCode);

    const bool result = (errorCode == ok || errorCode == stackIsEmpty) &&
        memcmp(postfixExpression, queueExpression, TEST_EXPRESSION_LENGTH) == 0;

    free(queueExpression);
    return result;
}

static bool testSpaceCase(void)
{
    const char* const infixExpression = "9 / (6 - 7) * 2 * (1 + 1)";
    const char* const postfixExpression = "9 6 7 - / 2 * 1 1 + *";

    ErrorCode errorCode;
    char* queueExpression = getPostfixExpression(infixExpression, &errorCode);

    const bool result = (errorCode == ok || errorCode == stackIsEmpty) &&
        memcmp(postfixExpression, queueExpression, TEST_EXPRESSION_LENGTH) == 0;

    free(queueExpression);
    return result;
}

static bool testIncorrectCase(void)
{
    const char* const infixExpression = "- 2";
    ErrorCode errorCode;
    return getPostfixExpression(infixExpression, &errorCode) == NULL;
}

bool passTests(void)
{
    return testOrdinaryCase() && testSpaceCase() && testIncorrectCase();
}
