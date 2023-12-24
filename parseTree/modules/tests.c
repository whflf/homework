#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "errors.h"
#include "tree.h"
#include "tests.h"

static bool testParseTreeOnFile(
    const char* const filename,
    const char* const expectedTreeStr,
    const int expectedResult,
    const bool isDivisionByZeroTest
)
{
    ErrorCode error = ok;
    Node* parseTree = fileToTree(filename, &error);
    if (error != ok)
    {
        return false;
    }

    FILE* const testOutputFile = tmpfile();
    if (testOutputFile == NULL)
    {
        return false;
    }

    printTree(parseTree, testOutputFile);
    fseek(testOutputFile, 0, SEEK_SET);

    const size_t expectedLength = strlen(expectedTreeStr);

    char* const testOutput = calloc(expectedLength + 1, sizeof(char));
    if (testOutput == NULL)
    {
        deleteTree(&parseTree);
        fclose(testOutputFile);
        return false;
    }

    fread(testOutput, sizeof(char), expectedLength, testOutputFile);
    
    bool isDivisionByZero = false;
    const bool result =
        strcmp(testOutput, expectedTreeStr) == 0 &&
        getResult(parseTree, &isDivisionByZero) == expectedResult &&
        isDivisionByZero == isDivisionByZeroTest;

    deleteTree(&parseTree);
    fclose(testOutputFile);
    free(testOutput);

    return result;
}

bool passTests(void)
{
    return
        testParseTreeOnFile("testFiles/test1.txt", "( / ( * 26 12 ) ( - 99 96 ) )", 104, false) &&
        testParseTreeOnFile("testFiles/test2.txt", "( + ( * 5 ( - 3 2 ) ) ( / 12 3 ) )", 9, false);
        testParseTreeOnFile("testFiles/test3.txt", "( / 120 0 )", 0, true);
}
