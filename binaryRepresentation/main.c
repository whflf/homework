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

int scanfSafetyChecks(int scanfFieldsFilled)
{
	char extraInput = 0;

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

char* const binary(int x)
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
		if (x & bit)
		{
			binaryNumber[i] = 1;
		}
		else
		{
			binaryNumber[i] = 0;
		}
		bit = bit >> 1;
	}

	return binaryNumber;
}

char* const binarySum(char* const x, char* const y)
{
	char* const binarySum = (int*)calloc(DIGITS, sizeof(char));
	if (binarySum == NULL)
	{
		return NULL;
	}

	char additionalDigit = 0;

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

int decimal(char* const x)
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

void printBinary(char* const x)
{
	for (size_t i = 0; i < DIGITS; ++i)
	{
		printf("%d", x[i]);
	}
}

bool testPositiveCase()
{
	int x = 5, y = 8;
	char* binaryX = binary(x),
		* binaryY = binary(y),
		* sumOfXAndY = binarySum(binaryX, binaryY);
	char correctSum[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1 };
	bool result = memcmp(sumOfXAndY, correctSum, DIGITS) == 0 && decimal(sumOfXAndY) == 13;
	free(binaryX);
	free(binaryY);
	free(sumOfXAndY);
	return result;
}

bool testNegativeCase()
{
	int x = 5, y = -6;
	char* binaryX = binary(x),
		* binaryY = binary(y),
		* sumOfXAndY = binarySum(binaryX, binaryY);
	char correctSum[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	bool result = memcmp(sumOfXAndY, correctSum, DIGITS) == 0 && decimal(sumOfXAndY) == -1;
	free(binaryX);
	free(binaryY);
	free(sumOfXAndY);
	return result;
}

int main(void)
{
	if (!testPositiveCase() && !testNegativeCase())
	{
		printf("~Tests failed");
		return TESTS_FAILED;
	}

	setlocale(LC_ALL, "ru-RU");

	int x = 0, y = 0;

	printf("> Введите х: ");
	int scanfError;
	if (scanfError = scanfSafetyChecks(scanf_s("%d", &x)))
	{
		return scanfError;
	}

	printf("> Введите у: ");
	if (scanfError = scanfSafetyChecks(scanf_s("%d", &y)))
	{
		return scanfError;
	}

	char* const binaryX = binary(x);
	if (binaryX == NULL)
	{
		printf("~ Memory allocation has failed");
		return OUT_OF_MEMORY;
	}
	char* const binaryY = binary(y);
	if (binaryY == NULL)
	{
		printf("~ Memory allocation has failed");
		free(binaryX);
		return OUT_OF_MEMORY;
	}

	printf("Двоичное представление числа х: ");
	printBinary(binaryX);
	printf("\nДвоичное представление числа у: ");
	printBinary(binaryY);

	printf("\nДвоичное представление суммы чисел х и у: ");
	char* const sumOfXAndY = binarySum(binaryX, binaryY);
	if (sumOfXAndY == NULL)
	{
		printf("~ Memory allocation has failed");
		free(binaryX);
		free(binaryY);
		return OUT_OF_MEMORY;
	}
	printBinary(sumOfXAndY);

	printf("\nДесятичное представление суммы чисел х и у: %d", decimal(sumOfXAndY));

	free(binaryX);
	free(binaryY);
	free(sumOfXAndY);

	return OK;
}
