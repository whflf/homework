#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define LENGTH 100000
#define OK 0
#define NEGATIVE_NUMBER_ERROR -1
#define OUT_OF_MEMORY 1
#define TESTS_FAILED 2
#define SCANF_FIELDS_ERROR

typedef int* (SortMethod)(size_t const* const, const size_t);

void swap(int* const value1, int* const value2)
{
    int value1Prev = *value1;
    *value1 = *value2;
    *value2 = value1Prev;
}

int arrayMax(int* const array, const size_t size)
{
    int maximum = 0;
    for (int i = 0; i < size; ++i)
    {
        maximum = max(maximum, array[i]);
    }
    return maximum;
}

int bubbleSort(int* const array, const size_t size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = (size - 1); j > i; --j)
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
    int* countingArray = (int*)calloc(maxNumber, maxNumber * sizeof(*array));
    if (countingArray == NULL) {
        return OUT_OF_MEMORY;
    }

    for (int i = 0; i < size; ++i) 
    {
        if (array[i] < 0) 
        {
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

double calcDuration(SortMethod method, const* const array, const size_t arraySize)
{
    clock_t start = clock();
    method(array, arraySize);
    clock_t stop = clock();
    return (stop - start) / CLOCKS_PER_SEC;
}

int* randArray(const size_t size, const int rangeMax, const int rangeMin)
{
    int* const randomNumbers = (int*)malloc(size * sizeof(int));

    if (randomNumbers == NULL) 
    {
        return NULL;
    }
    else 
    {
        srand(time(NULL));
        for (size_t i = 0; i < size; ++i) 
        {
            randomNumbers[i] = ((double)rand() / RAND_MAX) * (rangeMax - rangeMin) + rangeMin;
        }
    }

    return randomNumbers;
}

bool testCorrectCase()
{
    int sortedArray[5] = { 1, 2, 3, 4, 5 };
    int unsortedArray1[5] = { 2, 5, 4, 3, 1 };
    int unsortedArray2[5] = { 2, 5, 4, 3, 1 };
    bubbleSort(unsortedArray1, 5);
    countingSort(unsortedArray2, 5);
    return (memcmp(unsortedArray1, sortedArray, 5) == 0) && (memcmp(unsortedArray2, sortedArray, 5) == 0);
}

bool testIncorrectCase()
{
    int unsortedArray[5] = { -2, 5, -4, 3, 1 };
    return countingSort(unsortedArray, 5) == -1;
}

bool testBoundaryCase()
{
    int unsortedArray1[5] = { 1, 2, 3, 4, 5 };
    int unsortedArray2[5] = { 1, 2, 3, 4, 5 };
    int sortedArray[5] = { 1, 2, 3, 4, 5 };
    bubbleSort(unsortedArray1, 5);
    countingSort(unsortedArray2, 5);
    return (memcmp(unsortedArray1, sortedArray, 5) == 0) && (memcmp(unsortedArray2, sortedArray, 5) == 0);
}

int main()
{
    if (!testCorrectCase() || !testIncorrectCase() || !testBoundaryCase())
    {
        printf("~ Tests failed");
        return TESTS_FAILED;
    }

    size_t length = 0;
    printf("> Enter the length: ");

    int errorCode = 0;
    errorCode = scanf_s("%d", &length);
    if (errorCode == 0)
    {
        printf("!! Please enter an integer !!");
        return SCANF_FIELDS_ERROR;
    }
    if (length < 0) {
        printf("!! The length cannot be negative !!");
        return NEGATIVE_NUMBER_ERROR;
    }

    const* const numbers = (int*)malloc(length * sizeof(int));
    if (numbers == NULL) 
    {
        printf("Memory allocation failed :(");
        return OUT_OF_MEMORY;
    }

    printf("> Enter the elements of the array:\n");
    for (size_t i = 0; i < length; i++)
    {
        printf("a[%d] = ", i);
        errorCode = scanf_s("%d", &numbers[i]);
        if (errorCode == 0) 
        {
            printf("!! Enter only integers !!");
            free(numbers);
            return SCANF_FIELDS_ERROR;
        }
    }

    errorCode = countingSort(numbers, length);
    if (errorCode != 0) 
    {
        printf("!! Elements cannot be negative !! ");
        free(numbers);
        return NEGATIVE_NUMBER_ERROR;
    }
    for (size_t i = 0; i < length; ++i)
    {
        printf("%d ", numbers[i]);
    }
    free(numbers);

    printf("\n");

    const int randRangeMax = 1000;
    const int randRangeMin = 0;
    const* const randomNumbers = randArray(LENGTH, randRangeMax, randRangeMin);
    if (randomNumbers == NULL)
    {
        printf("Memory allocation has failed :(");
        return OUT_OF_MEMORY;
    }

    const* const randomNumbers2 = (int*)malloc(LENGTH * sizeof(int));
    if (randomNumbers2 == NULL) 
    {
        printf("Memory allocation has failed :(");
        return OUT_OF_MEMORY;
    }
    memcpy(randomNumbers2, randomNumbers, LENGTH);

    double duration = calcDuration(bubbleSort, randomNumbers, LENGTH);
    printf("Bubble sorting has required %2.10f seconds\n", duration);

    duration = calcDuration(countingSort, randomNumbers2, LENGTH);
    printf("Counting sorting has required %2.10f seconds\n", duration);

    free(randomNumbers);
    free(randomNumbers2);
    
    return OK;
}