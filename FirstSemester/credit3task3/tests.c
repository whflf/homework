#include <stdlib.h>

#include "tests.h"
#include "lexer.h"

static bool test1(void)
{
    return isCorrect("Q1W2E3R4.R_%-TY+@ABC123.123ABC.C");
}

static bool test2(void)
{
    return !isCorrect("EUIW(&FV23=");
}

bool passTests(void)
{
    return test1() && test2();
}
