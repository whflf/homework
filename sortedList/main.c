#include <stdio.h>
#include <stdlib.h>

#include "include/errors.h"
#include "include/list.h"
#include "dialogue.h"
#include "tests.h"

int main(void)
{
    if (!passTests())
    {
        printf("%s", errorMessages[testsFailed]);
    }
    List* myList = NULL;
    programLoop(&myList);
    deleteList(&myList);
    return ok;
}
