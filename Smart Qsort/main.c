#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define RETURN_OK 0
#define RETURN_TESTS_FAILED 1
#define RETURN_OUT_OF_MEMORY 2
#define RETURN_BAD_INPUT 3

void swap(int* const value1, int* const value2)
{
    const int value1Prev = *value1;
    *value1 = *value2;
    *value2 = value1Prev;
}

void insertionSort(int* const array, const size_t low, const size_t high)
{
    for (size_t i = low; i < high; ++i)
    {
        if (i == low && low == 0)
        {
            continue;
        }
        size_t j = i - 1;
        while (array[j + 1] < array[j])
        {
            swap(&array[j + 1], &array[j]);
            --j;
        }
    }
}

size_t partition(int* const array, const size_t low, const size_t high)
{
    const int pivot = array[high];
    size_t i = (low - 1);

    for (size_t j = low; j < high; ++j)
    {
        if (array[j] <= pivot)
        {
            ++i;
            if (i != j)
            {
                swap(&array[i], &array[j]);
            }
        }
    }

    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quicksort(int* const array, const size_t low, const size_t high)
{
    if (low < high)
    {
        size_t partitionIndex = high;
        if (high - low > 10)
        {
            partitionIndex = partition(array, low, high);
        }

        if ((partitionIndex - low) >= 10)
        {
            quicksort(array, low + 1, partitionIndex - 1);
        }
        else
        {
            insertionSort(array, low, partitionIndex + 1);
        }
        if ((high - partitionIndex) >= 10)
        {
            quicksort(array, partitionIndex + 1, high);
        }
        else
        {
            insertionSort(array, partitionIndex, high + 1);
        }
    }
}

bool testCorrectCase()
{
    int unsortedArray[] = { 2, 5, 4, 3, 1 };
    const int sortedArray[] = { 1, 2, 3, 4, 5 };
    quicksort(unsortedArray, 0, _countof(unsortedArray) - 1);
    return memcmp(unsortedArray, sortedArray, _countof(unsortedArray)) == 0;
}

bool testBoundaryCase()
{
    int unsortedArray[] = { 1, 2, 3, 4, 5 };
    const int sortedArray[] = { 1, 2, 3, 4, 5 };
    quicksort(unsortedArray, 0, _countof(unsortedArray) - 1);
    return memcmp(unsortedArray, sortedArray, _countof(unsortedArray)) == 0;
}

int main()
{
    if (!testCorrectCase() || !testBoundaryCase())
    {
        printf("~ Tests failed");
        return RETURN_TESTS_FAILED;
    }

    size_t size = 0;

    printf("> Enter array size: ");

    if (!scanf("%llu", &size))
    {
        printf("\nBad input for array size. Please enter a valid positive integer.\n");
        return RETURN_BAD_INPUT;
    }

    int* numbers = (int*)malloc(size * sizeof(int));
    if (numbers == NULL)
    {
        printf("Memory allocation has failed :(");
        return RETURN_OUT_OF_MEMORY;
    }
    for (size_t i = 0; i < size; ++i)
    {
        printf("> a[%d] = ", (int)i);
        if (!scanf("%d", &numbers[i]))
        {
            printf("\nBad input for a[%llu]. Please enter a valid integer.\n", i);
            return RETURN_BAD_INPUT;
        }
    }

    quicksort(numbers, 0, size - 1);

    printf("\nResult: ");
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d", numbers[i]);
        if (i < size - 1)
        {
            printf(", ");
        }
    }
    printf("\n");

    free(numbers);
    return RETURN_OK;
}

