#include "include/errors.h"
#include "mostOccurredElement.h"
#include "tests.h"

#define FILE_NAME_TEST_CORRECT "staticFiles/testCorrectFile.txt"
#define FILE_NAME_TEST_MIXED "staticFiles/testMixedFile.txt"
#define FILE_NAME_TEST_BAD "staticFiles/testBadFile.txt"

static bool sharedFileTest(const char* const filename, const int expectedValue, const ErrorCode expectedError)
{
    int mostOccurredElementValue = 0;
    const ErrorCode error = getMostOccurredElementFromFile(filename, &mostOccurredElementValue);
    return error == expectedError && mostOccurredElementValue == expectedValue;
}

bool passTests(void)
{
    const bool testResultCorrectFile = sharedFileTest(FILE_NAME_TEST_CORRECT, 42, ok),
        testResultMixedFile = sharedFileTest(FILE_NAME_TEST_MIXED, -3, ok),
        testResultBadFile = sharedFileTest(FILE_NAME_TEST_BAD, 0, emptyArray);

    return testResultCorrectFile && testResultMixedFile && testResultBadFile;
}
