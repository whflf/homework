#include <stdlib.h>
#include <stdbool.h>

#include "include/stack.h"
#include "include/errors.h"

#define JAVASCRIPT_CODE_FOR_TEST "                   \
function printInputFirstChar(string) {               \
    alert('Your input first character: '+string[0]); \
}                                                    \
printInputFirstChar(prompt('Enter something:'));     \
"

static bool testCorrectCase(void)
{
    ErrorCode errorCode = ok;
    return parenthesisCheck("([{}])", &errorCode);
}

static bool testIncorrectCase(void)
{
    ErrorCode errorCode = ok;
    return !parenthesisCheck("({)}", &errorCode);
}

static bool testRealCodeCase(void)
{
    ErrorCode errorCode = ok;
    return parenthesisCheck(JAVASCRIPT_CODE_FOR_TEST, &errorCode);
}

bool passTests(void)
{
    return testCorrectCase() && testIncorrectCase() && testRealCodeCase();
}
