#include <stdlib.h>
#include <stdio.h>

#include "tests.h"
#include "errors.h"

int main(void)
{
    const ErrorCode error = passTests() ? ok : testsFailed;
    return printErrorMessage(error);
}

