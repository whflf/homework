#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define BAD_INPUT 1
#define TESTS_FAILED 2

#define MAX_DIGITS_NUMBER 10

int compareCharacters(const char* const a, const char* const b)
{
    return (int)*a - (int)*b;
}

int getMinNumber(char* const stringNumber)
{
    qsort(stringNumber, strlen(stringNumber), sizeof(char), compareCharacters);
    return atoi(stringNumber);
}

bool test1(void)
{
    const char testString[6] = "48103";
    const int expectedNumber = 1348;

    return getMinNumber(testString) == expectedNumber;
}

bool test2(void)
{
    const char testString[6] = "12345";
    const int expectedNumber = 12345;

    return getMinNumber(testString) == expectedNumber;
}

bool test3(void)
{
    const char testString[6] = "54321";
    const int expectedNumber = 12345;

    return getMinNumber(testString) == expectedNumber;
}

bool test4(void)
{
    const char testString[6] = "11111";
    const int expectedNumber = 11111;

    return getMinNumber(testString) == expectedNumber;
}

int main(void)
{
    if (!test1() || !test2() || !test3() || !test4())
    {
        printf("~ Tests failed.\n");
        return TESTS_FAILED;
    }
    printf("> Enter a natural number: ");

    const int tempNumber = 0;
    char number[MAX_DIGITS_NUMBER + 1] = { '\0' };
    scanf("%s", number);

    if (atoi(number) == 0)
    {
        printf("\nPlease enter a valid natural number.\n");
        return BAD_INPUT;
    }

    printf("\nMinimum number of given digits: %d\n", getMinNumber(number));
    return OK;
}
