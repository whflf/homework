#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "tests.h"

#define OK 0
#define TESTS_FAILED 1

int main(void)
{
    if (!passTests())
    {
        printf("Tests failed.\n");
        return TESTS_FAILED;
    }

    printf("OK\n");
    return OK;
}
