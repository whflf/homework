#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define RETURN_OK 0
#define RETURN_TESTS_FAILED 1
#define RETURN_OUT_OF_MEMORY 2
#define RETURN_BAD_INPUT 3

#define countof(array) sizeof(array) / sizeof(array[0])

void swap(int* const value1, int* const value2)
{
    const int value1Prev = *value1;
    *value1 = *value2;
    *value2 = value1Prev;
}

void insertionSort(int* const array, const size_t low, const size_t high)
{
    for (size_t i = low + 1; i < high; ++i)
    {
        for (size_t j = i - 1; array[j + 1] < array[j]; --j)
        {
            swap(&array[j + 1], &array[j]);
        }
    }
}

size_t partition(int* const array, const size_t low, const size_t high)
{
    const int pivot = array[high];
    size_t i = low - 1;

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
    return i + 1;
}

void quicksort(int* const array, const size_t low, const size_t high)
{
    if (low >= high)
    {
        return;
    }

    if (high - low < 9)
    {
        insertionSort(array, low, high + 1);
        return;
    }

    const size_t partitionIndex = partition(array, low, high);
    quicksort(array, low + 1, partitionIndex - 1);
    quicksort(array, partitionIndex + 1, high);
}

bool testCorrectCase(void)
{
    int unsortedArray[] = { 2, 5, 4, 3, 1 };
    const int sortedArray[] = { 1, 2, 3, 4, 5 };
    quicksort(unsortedArray, 0, countof(unsortedArray) - 1);
    return memcmp(unsortedArray, sortedArray, countof(unsortedArray)) == 0;
}

bool testBoundaryCase(void)
{
    int unsortedArray[] = { 1, 2, 3, 4, 5 };
    const int sortedArray[] = { 1, 2, 3, 4, 5 };
    quicksort(unsortedArray, 0, countof(unsortedArray) - 1);
    return memcmp(unsortedArray, sortedArray, countof(unsortedArray)) == 0;
}

int main(int argc, char* argv[])
{
    if (argc > 1 && strcmp(argv[1], "run tests") == 0)
    {
        return testCorrectCase() && testBoundaryCase() ? 0 : 1;
    }

    if (!testCorrectCase() || !testBoundaryCase())
    {
        printf("~ Tests failed.\n");
        return RETURN_TESTS_FAILED;
    }

    size_t size = 0;

    printf("> Enter array size: ");
    if (!scanf("%zu", &size) || size == 0)
    {
        printf("\nBad input for array size. Please enter a non-zero positive integer.\n");
        return RETURN_BAD_INPUT;
    }

    int* const numbers = (int*)malloc(size * sizeof(int));
    if (numbers == NULL)
    {
        printf("\nMemory allocation has failed :(\n");
        return RETURN_OUT_OF_MEMORY;
    }

    for (size_t i = 0; i < size; ++i)
    {
        printf("> a[%zu] = ", i);
        if (!scanf("%d", &numbers[i]))
        {
            printf("\nBad input for a[%zu]. Please enter a valid integer.\n", i);
            free(numbers);
            return RETURN_BAD_INPUT;
        }
    }

    quicksort(numbers, 0, size - 1);

    printf("\nResult: ");
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d%s", numbers[i], i < size - 1 ? ", " : "\n");
    }

    free(numbers);

    return RETURN_OK;
}
