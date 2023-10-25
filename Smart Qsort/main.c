#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RETURN_OK 0
#define RETURN_TESTS_FAILED 1
#define RETURN_OUT_OF_MEMORY 2

void swap(int* const value1, int* const value2)
{
    const int value1Prev = *value1;
    *value1 = *value2;
    *value2 = value1Prev;
}

void insertionSort(int* const array, const int low, const int high)
{
    for (size_t i = low; i <= high - 1; ++i)
    {
        if (i == low && low == 0)
        {
            continue;
        }
        int j = i - 1;
        while (array[j + 1] < array[j])
        {
            swap(&array[j + 1], &array[j]);
            --j;
        }
    }
}

int partition(int array[], const int low, const int high)
{
    const int pivot = array[high];
    size_t i = (low - 1);

    for (size_t j = low; j <= high - 1; ++j)
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

void quicksort(int array[], const int low, const int high)
{
    if (low < high)
    {
        const int partitionIndex = partition(array, low, high);
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
    const int unsortedArray[5] = { 2, 5, 4, 3, 1 };
    const int sortedArray[5] = { 1, 2, 3, 4, 5 };
    quicksort(unsortedArray, 0, 4);
    return memcmp(unsortedArray, sortedArray, 5) == 0;
}

bool testBoundaryCase()
{
    const int unsortedArray[5] = { 1, 2, 3, 4, 5 };
    const int sortedArray[5] = { 1, 2, 3, 4, 5 };
    quicksort(unsortedArray, 0, 4);
    return memcmp(unsortedArray, sortedArray, 5) == 0;
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

    fgets(&size, sizeof(size_t) + 1, stdin);

    size = atoi(&size);

    int* numbers = (int*)malloc(size * sizeof(int));
    if (numbers == NULL) 
    {
        printf("Memory allocation has failed :(");
        return RETURN_OUT_OF_MEMORY;
    }
    for (size_t i = 0; i < size; ++i)
    {
        printf("> a[%d] = ", (int)i);
        fgets(&numbers[i], sizeof(int) + 1, stdin);
        numbers[i] = atoi(&numbers[i]);
    }

    quicksort(numbers, 0, size - 1);

    printf("Result: ");
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
