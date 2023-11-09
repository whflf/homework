#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

#define DIGITS 31

#define TESTS_FAILED -1
#define OK
#define WRONG_SCANF_FIELDS_ERROR 1;
#define EXTRA_INPUT_ERROR 2;
#define OUT_OF_MEMORY 4;

int scanfSafetyChecks(int scanfFieldsFilled)
{
    char extraInput = { '\0' };

    if (!scanfFieldsFilled) 
    {
        printf("!! Неверный ввод. Пожалуйста, введите целое число !!");
        return WRONG_SCANF_FIELDS_ERROR;
    }
    if (scanf_s("%c", &extraInput) != EOF && extraInput != '\n') 
    {
        printf("!! Пожалуйста, введите целое число без лишних знаков !!");
        return EXTRA_INPUT_ERROR;
    }
    return 0;
}

int* const binary(int x)
{
    if (x < 0) 
    {
        x = (1 << DIGITS) + x;
    }

    int* const binaryNumber = (int*)calloc(DIGITS, sizeof(int));
    if (binaryNumber == NULL) 
    {
        return NULL;
    }

    int i = 0;

    int bit = 0b1000000000000000000000000000000;

    for (int j = 0; j < DIGITS; ++j) 
    {
        if (x & bit) 
        {
            binaryNumber[i] = 1;
        }
        else
        {
            binaryNumber[i] = 0;
        }
        bit = bit >> 1;
        ++i;
    }

    return binaryNumber;
}

int* const binarySum(int* const x, int* const y) 
{
    int* const binarySum = (int*)calloc(DIGITS, sizeof(int));
    if (binarySum == NULL) 
    {
        return NULL;
    }

    int additionalDigit = 0;

    for (int i = DIGITS - 1; i >= 0; --i) 
    {
        int sum = x[i] + y[i] + additionalDigit;
        if (sum > 1) 
        {
            if (sum == 3) 
            {
                binarySum[i] = 1;
            }
            additionalDigit = 1;
        }
        else 
        {
            binarySum[i] = sum;
            additionalDigit = 0;
        }
    }

    return binarySum;
}

int decimal(int* const x) 
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

void printBinary(int* const x)
{
    for (size_t i = 0; i < DIGITS; ++i)
    {
        printf("%d", x[i]);
    }
}

bool testPositiveCase()
{
    int x = 5;
    int y = 8;
    int* sumOfXAndY = binarySum(binary(x), binary(y));
    int correctSum[DIGITS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1};
    return memcmp(sumOfXAndY, correctSum, 5) == 0 && decimal(sumOfXAndY) == 13;
}

bool testNegativeCase()
{
    int x = 5;
    int y = -6;
    int* sumOfXAndY = binarySum(binary(x), binary(y));
    int correctSum[DIGITS] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    return memcmp(sumOfXAndY, correctSum, 5) == 0 && decimal(sumOfXAndY) == -1;
}

int main()
{
    if (!testPositiveCase()) 
    {
        printf("~Tests failed");
        return TESTS_FAILED;
    }

    setlocale(LC_ALL, "ru-RU");

    int x = 0;
    int y = 0;

    printf("> Введите х: ");
    if (scanfSafetyChecks(scanf_s("%d", &x))) 
    {
        return 1;
    }

    printf("> Введите у: ");
    if (scanfSafetyChecks(scanf_s("%d", &y))) 
    {
        return 1;
    }

    int* const binaryX = binary(x);
    if (binaryX == NULL)
    {
        printf("~ Memory allocation has failed");
        return OUT_OF_MEMORY;
    }
    int* const binaryY = binary(y);
    if (binaryY == NULL)
    {
        printf("~ Memory allocation has failed");
        return OUT_OF_MEMORY;
    }

    printf("Двоичное представление числа х: ");
    printBinary(binaryX);
    printf("\nДвоичное представление числа у: ");
    printBinary(binaryY);

    printf("\nДвоичное представление суммы чисел х и у: ");
    int* const sumOfXAndY = binarySum(binaryX, binaryY);
    if (sumOfXAndY == NULL)
    {
        printf("~ Memory allocation has failed");
        return OUT_OF_MEMORY;
    }
    printBinary(sumOfXAndY);

    printf("\nДесятичное представление суммы чисел х и у: %d", decimal(sumOfXAndY));

    free(binaryX);
    free(binaryY);
    free(sumOfXAndY);
    return 0;
}
