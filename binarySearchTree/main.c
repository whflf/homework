#include <stdlib.h>

#include "tree.h"
#include "dialogue.h"
#include "errors.h"
#include "tests.h"

int main(void)
{
    if (!passTests())
    {
        printf("Tests failed. Exiting.\n");
        return testsFailed;
    }
    Node* dictionary = NULL;
    programLoop(&dictionary);
    deleteTree(&dictionary);
    return ok;
}
