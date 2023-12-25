#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tests.h"

static bool testPrintCommentsToFile(const char* const filename, const char* const expectedStrings)
{
    FILE* const testInputFile = fopen(filename, "r");
    if (testInputFile == NULL)
    {
        return false;
    }

    FILE* const testOutputFile = tmpfile();
    if (testOutputFile == NULL)
    {
        return false;
    }

    const ErrorCode error = printComments(testInputFile, testOutputFile);
    fseek(testOutputFile, 0, SEEK_SET);

    const size_t expectedLength = strlen(expectedStrings);
    char* const testOutput = (char*)calloc(expectedLength + 1, sizeof(char));
    if (testOutput == NULL)
    {
        fclose(testOutputFile);
        return false;
    }

    fread(testOutput, sizeof(char), expectedLength, testOutputFile);
    const bool result = strcmp(testOutput, expectedStrings) == 0;

    free(testOutput);
    fclose(testInputFile);
    fclose(testOutputFile);

    return result;
}

bool passTests(void)
{
    return
        testPrintCommentsToFile("testFiles/test1.txt", "/* comment 1 */\n\n/* comment 2 */\n\n") &&
        testPrintCommentsToFile("testFiles/test2.txt",
            "/*Lorem ipsum dolor sit amet, \nconsectetur adipiscing elit, \nsed do eiusmod tempor incididunt \nut labore et dolore magna aliqua.*/\n\n") &&
        testPrintCommentsToFile("testFiles/test3.txt", "");
}
