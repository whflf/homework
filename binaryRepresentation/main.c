#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

#define DIGITS 31

#define TESTS_FAILED -1
#define OK 0
#define WRONG_SCANF_FIELDS_ERROR 1
#define EXTRA_INPUT_ERROR 2
#define OUT_OF_MEMORY 3
#define FAILED_TO_ALLOCATE_MEMORY_TEXT "~Не удалось выделить память.\n"

int scanfSafetyChecks(const int scanfFieldsFilled)
{
    const char extraInput = 0;

    if (!scanfFieldsFilled)
    {
        printf("!! Неверный ввод. Пожалуйста, введите целое число !!");
        return WRONG_SCANF_FIELDS_ERROR;
    }

    if (scanf("%c", &extraInput) != EOF && extraInput != '\n')
    {
        printf("!! Пожалуйста, введите целое число без лишних знаков !!");
        return EXTRA_INPUT_ERROR;
    }

    return OK;
}

char* binary(int x)
{
    if (x < 0)
    {
        x = (1 << DIGITS) + x;
    }

    char* const binaryNumber = (char*)calloc(DIGITS, sizeof(char));
    if (binaryNumber == NULL)
    {
        return NULL;
    }

    int bit = 1 << DIGITS - 1;

    for (int i = 0; i < DIGITS; ++i)
    {
        binaryNumber[i] = x & bit ? 1 : 0;
        bit = bit >> 1;
    }

    return binaryNumber;
}

char* binarySum(const char* const x, const char* const y)
{
    char* const binarySum = (char*)calloc(DIGITS, sizeof(char));
    if (binarySum == NULL)
    {
        return NULL;
    }

    char additionalDigit = 0;

    for (int i = DIGITS - 1; i >= 0; --i)
    {
        const int sum = x[i] + y[i] + additionalDigit;
        binarySum[i] = sum % 2;
        additionalDigit = sum / 2;
    }

    return binarySum;
}

int decimal(const char* const x)
{
    int decimalNumber = 0;

    for (int i = 0; i < DIGITS; ++i)
    {
        int degree = DIGITS - 1 - i;
        decimalNumber += (1 << degree) * x[i];
    }

    if (x[0] == 1)
    {
        decimalNumber = -((1 << DIGITS) - decimalNumber);
    }
    return decimalNumber;
}

void printBinary(const char* const x)
{
    for (size_t i = 0; i < DIGITS; ++i)
    {
        printf("%d", x[i]);
    }
}

bool sumTest(const int x, const int y, const char* const expectedBinaryValue, const int expectedIntValue)
{
    const char* const binaryX = binary(x);
    const char* const binaryY = binary(y);
    const char* const sumOfXAndY = binarySum(binaryX, binaryY);

    if (binaryX == NULL || binaryY == NULL || sumOfXAndY == NULL)
    {
        free(binaryX);
        free(binaryY);
        free(sumOfXAndY);
        printf(FAILED_TO_ALLOCATE_MEMORY_TEXT);
        return false;
    }

    bool result = memcmp(sumOfXAndY, expectedBinaryValue, DIGITS) == 0 && decimal(sumOfXAndY) == expectedIntValue;

    free(binaryX);
    free(binaryY);
    free(sumOfXAndY);

    return result;
}

bool testPositiveCase(void)
{
    int const x = 5, const y = 8;

    const char correctSumBits[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1
    };

    const int correctSum = 13;

    return sumTest(x, y, correctSumBits, correctSum);
}

bool testNegativeCase(void)
{
    int const x = 5, const y = -6;

    const char correctSumBits[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };

    const int correctSum = -1;

    return sumTest(x, y, correctSumBits, correctSum);
}

int main(void)
{
    setlocale(LC_ALL, "ru-RU");

    if (!testPositiveCase() || !testNegativeCase())
    {
        printf("~ Тесты провалены.\n");
        return TESTS_FAILED;
    }

    int scanfError,
        x = 0, y = 0;

    printf("> Введите х: ");
    if (scanfError = scanfSafetyChecks(scanf("%d", &x)))
    {
        return scanfError;
    }

    printf("> Введите у: ");
    if (scanfError = scanfSafetyChecks(scanf("%d", &y)))
    {
        return scanfError;
    }

    const char* const binaryX = binary(x);
    const char* const binaryY = binary(y);
    const char* const sumOfXAndY = binarySum(binaryX, binaryY);

    if (binaryX == NULL || binaryY == NULL || sumOfXAndY == NULL)
    {
        free(binaryX);
        free(binaryY);
        free(sumOfXAndY);
        printf(FAILED_TO_ALLOCATE_MEMORY_TEXT);
        return OUT_OF_MEMORY;
    }

    printf("Двоичное представление числа х: ");
    printBinary(binaryX);

    printf("\nДвоичное представление числа у: ");
    printBinary(binaryY);

    printf("\nДвоичное представление суммы чисел х и у: ");
    printBinary(sumOfXAndY);

    printf("\nДесятичное представление суммы чисел х и у: %d\n", decimal(sumOfXAndY));

    free(binaryX);
    free(binaryY);
    free(sumOfXAndY);

    return OK;
}
