#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define LENGTH 100000
#define NEGATIVE_NUMBER_ERROR -1
#define OK 0
#define OUT_OF_MEMORY 1
#define TESTS_FAILED 2
#define SCANF_FIELDS_ERROR 3

#define countof(array) sizeof(array) / sizeof(array[0])

typedef int* (SortMethod)(int* const, const size_t);

void swap(int* const value1, int* const value2)
{
    int value1Prev = *value1;
    *value1 = *value2;
    *value2 = value1Prev;
}

int arrayMax(int* const array, const size_t size)
{
    int maximum = 0;
    for (size_t i = 0; i < size; ++i)
    {
        maximum = max(maximum, array[i]);
    }
    return maximum;
}

int bubbleSort(int* const array, const size_t size)
{
    for (size_t i = 0; i < size - 1; ++i)
    {
        for (size_t j = (size - 1); j > i; --j)
        {
            if (array[j - 1] > array[j])
            {
                swap(&array[j - 1], &array[j]);
            }
        }
    }
    return OK;
}

int countingSort(int* const array, const size_t size)
{
    const int maxNumber = arrayMax(array, size) + 1;
    int* countingArray = (int*)calloc(maxNumber, sizeof(int));
    if (countingArray == NULL)
    {
        return OUT_OF_MEMORY;
    }

    for (size_t i = 0; i < size; ++i)
    {
        if (array[i] < 0)
        {
            free(countingArray);
            return NEGATIVE_NUMBER_ERROR;
        }
        ++countingArray[array[i]];
    }
    size_t index = 0;
    for (size_t i = 0; i < maxNumber; ++i)
    {
        for (size_t j = 0; j < countingArray[i]; ++j)
        {
            array[index++] = i;
        }
    }
    free(countingArray);
    return OK;
}

double calcDuration(SortMethod method, int* const array, const size_t arraySize, int* const errorCode)
{
    clock_t start = clock();
    *errorCode = method(array, arraySize);
    clock_t stop = clock();
    return (double)(stop - start) / CLOCKS_PER_SEC;
}

int* randArray(const size_t size, const int rangeMax, const int rangeMin)
{
    int* const randomNumbers = (int*)malloc(size * sizeof(int));

    if (randomNumbers == NULL)
    {
        return NULL;
    }
    srand(time(NULL));

    for (size_t i = 0; i < size; ++i)
    {
        randomNumbers[i] = (int)(((double)rand() / RAND_MAX) * (rangeMax - rangeMin) + rangeMin);
    }

    return randomNumbers;
}

int compareSortingMethods(void)
{
    const int randRangeMax = 1000;
    const int randRangeMin = 0;
    int* const randomNumbers = randArray(LENGTH, randRangeMax, randRangeMin);
    if (randomNumbers == NULL)
    {
        printf("Memory allocation has failed :(");
        free(randomNumbers);
        return OUT_OF_MEMORY;
    }

    int* const randomNumbers2 = (int*)malloc(LENGTH * sizeof(int));
    if (randomNumbers2 == NULL)
    {
        printf("Memory allocation has failed :(");
        free(randomNumbers2);
        return OUT_OF_MEMORY;
    }
    memcpy(randomNumbers2, randomNumbers, LENGTH);
    int errorCode = OK;

    double duration = calcDuration(bubbleSort, randomNumbers, LENGTH, &errorCode);
    if (errorCode != OK)
    {
        return errorCode;
    }
    printf("Bubble sorting has required %2.10f seconds\n", duration);

    duration = calcDuration(countingSort, randomNumbers2, LENGTH, &errorCode);
    if (errorCode != 0)
    {
        return errorCode;
    }
    printf("Counting sorting has required %2.10f seconds\n", duration);

    free(randomNumbers);
    free(randomNumbers2);

    return OK;
}

bool compareArrays(size_t size, int* const array1, int* const array2)
{
    return memcmp(array1, array2, size) == 0;
}

bool testCorrectCase(void)
{
    int const sortedArray[] = { 1, 2, 3, 4, 5 };
    int unsortedArray1[] = { 2, 5, 4, 3, 1 };
    int unsortedArray2[] = { 2, 5, 4, 3, 1 };
    bubbleSort(unsortedArray1, countof(unsortedArray1));
    countingSort(unsortedArray2, countof(unsortedArray2));
    return compareArrays(countof(unsortedArray1), unsortedArray1, sortedArray) &&
        compareArrays(countof(unsortedArray2), unsortedArray2, sortedArray);
}

bool testIncorrectCase(void)
{
    int unsortedArray[] = { -2, 5, -4, 3, 1 };
    return countingSort(unsortedArray, countof(unsortedArray)) == NEGATIVE_NUMBER_ERROR;
}

bool testBoundaryCase(void)
{
    int const sortedArray[] = { 1, 2, 3, 4, 5 };
    int unsortedArray1[] = { 1, 2, 3, 4, 5 };
    int unsortedArray2[] = { 1, 2, 3, 4, 5 };
    bubbleSort(unsortedArray1, countof(unsortedArray1));
    countingSort(unsortedArray2, countof(unsortedArray2));
    return compareArrays(countof(unsortedArray1), unsortedArray1, sortedArray) &&
        compareArrays(countof(unsortedArray2), unsortedArray2, sortedArray);
}

int main(int argc, char* argv)
{
    if (argc > 1 && strcmp(argv[1], "run tests") == 0)
    {
        return testCorrectCase() || testIncorrectCase() || testBoundaryCase();
    }

    if (!testCorrectCase() || !testIncorrectCase() || !testBoundaryCase())
    {
        printf("~ Tests failed");
        return TESTS_FAILED;
    }

    size_t length = 0;
    printf("> Enter the length: ");

    int errorCode = 0;
    errorCode = scanf_s("%zu", &length);
    if (errorCode == 0)
    {
        printf("!! Please enter an integer !!");
        return SCANF_FIELDS_ERROR;
    }

    int* const numbers = (int*)malloc(length * sizeof(int));
    if (numbers == NULL)
    {
        printf("Memory allocation failed :(");
        return OUT_OF_MEMORY;
    }

    printf("> Enter the elements of the array:\n");
    for (size_t i = 0; i < length; i++)
    {
        printf("a[%zu] = ", i);
        errorCode = scanf_s("%d", &numbers[i]);
        if (errorCode == 0)
        {
            printf("!! Enter only integers !!");
            free(numbers);
            return SCANF_FIELDS_ERROR;
        }
    }

    errorCode = countingSort(numbers, length);
    if (errorCode == NEGATIVE_NUMBER_ERROR)
    {
        printf("!! Elements cannot be negative !! ");
        free(numbers);
        return NEGATIVE_NUMBER_ERROR;
    }
    if (errorCode == OUT_OF_MEMORY)
    {
        printf("Memory allocation has failed :(");
        free(numbers);
        return OUT_OF_MEMORY;
    }
    for (size_t i = 0; i < length; ++i)
    {
        printf("%d%s", numbers[i], i < length - 1 ? ", " : "\n");
    }
    free(numbers);

    errorCode = compareSortingMethods();
    if (errorCode != OK)
    {
        printf("~ Sorting methods comparing has failed");
        return errorCode;
    }

    return OK;
}
