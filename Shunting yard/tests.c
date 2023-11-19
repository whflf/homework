#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "queue.h"
#include "stack.h"
#include "tests.h"
#include "shuntingYard.h"

static bool testOrdinaryCase(void)
{
    const int expressionLength = 11;

    char* const infixExpression = "(5*6-9*3)+8/4";
    char* const postfixExpression = "56*93*-84/+";
    char* const queueExpression = getPostfixExpression(infixExpression);

    return memcmp(postfixExpression, queueExpression, expressionLength) == 0;
}

static bool testSpaceCase(void)
{
    const int expressionLength = 11;

    char* const infixExpression = "9 / (6 - 7) * 2 * (1 + 1)";
    char* const postfixExpression = "967-/2*11+*";
    char* const queueExpression = getPostfixExpression(infixExpression);

    return memcmp(postfixExpression, queueExpression, expressionLength) == 0;
}

static bool testIncorrectCase(void)
{
    char* const infixExpression = "- 2";
    return getPostfixExpression(infixExpression) == NULL;
}

bool passTests(void)
{
    return testOrdinaryCase() && testSpaceCase() && testIncorrectCase;
}
