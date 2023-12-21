#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define OK 0
#define TESTS_FAILED 1

unsigned int getDecimal(const bool* const number, const size_t size)
{
    unsigned int result = 0;

    for (int i = size - 1; i > -1; --i)
    {
        result += (number[i]) * (1 << (size - i - 1));
    }

    return result;
}

int compareBinaryNumbers(const bool* const firstNumber, const size_t firstNumberSize, const bool* const secondNumber, const size_t secondNumberSize)
{
    return getDecimal(firstNumber, firstNumberSize) - getDecimal(secondNumber, secondNumberSize);
}

bool test1(void)
{
    bool firstNumber[] = { true, false, false };
    bool secondNumber[] = { true, false, false, false };

    return compareBinaryNumbers(firstNumber, 3, secondNumber, 4) == -4;
}

bool test2(void)
{
    bool firstNumber[] = { true, false, false };
    bool secondNumber[] = { true, false, false };

    size_t sizetest = sizeof(firstNumber);

    return compareBinaryNumbers(firstNumber, 3, secondNumber, 3) == 0;
}

bool test3(void)
{
    bool firstNumber[] = { true, false, true, true };
    bool secondNumber[] = { true, false, false };

    return compareBinaryNumbers(firstNumber, 4, secondNumber, 3) == 7;
}

int main(void)
{
    if (!test1() || !test2() || !test3())
    {
        printf("~ Tests failed.\n");
        return TESTS_FAILED;
    }

    bool firstNumber[] = { true, false, false };
    bool secondNumber[] = { true, false, false, false };

    const int result = compareBinaryNumbers(firstNumber, 3, secondNumber, 4);

    printf("The first number is %s the second.\n", result > 0 ? "greater than" : (result == 0 ? "equal to" : "less than"));
}
