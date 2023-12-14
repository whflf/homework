#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RETURN_OK 0
#define RETURN_TESTS_FAILED 1
#define RETURN_OUT_OF_MEMORY 2

void swap(int* const value1, int* const value2)
{
    const int value1Previous = *value1;
    *value1 = *value2;
    *value2 = value1Previous;
}

void shellSort(int* const array, const size_t size) 
{
    for (int s = size / 2; s > 0; s /= 2) 
    {
        for (int i = s; i < size; ++i) 
        {
            for (int j = i - s; j >= 0 && array[j] > array[j + s]; j -= s) 
            {
                swap(&array[j], &array[j + s]);
            }
        }
    }
}

bool testCorrectCase()
{
    const int unsortedArray[5] = { 2, 5, 4, 3, 1 };
    const int sortedArray[5] = { 1, 2, 3, 4, 5 };
    const size_t size = 5;
    shellSort(unsortedArray, size);
    return memcmp(unsortedArray, sortedArray, size) == 0;
}

bool testBoundaryCase1()
{
    const int unsortedArray[5] = { 1, 2, 3, 4, 5 };
    const int sortedArray[5] = { 1, 2, 3, 4, 5 };
    const size_t size = 5;
    shellSort(unsortedArray, size);
    return memcmp(unsortedArray, sortedArray, size) == 0;
}

bool testBoundaryCase2()
{
    const int unsortedArray[5] = { -1, -2, -3, -4, -5 };
    const int sortedArray[5] = { -5, -4, -3, -2, -1 };
    const size_t size = 5;
    shellSort(unsortedArray, size);
    return memcmp(unsortedArray, sortedArray, size) == 0;
}

int main()
{
    if (!testCorrectCase() || !testBoundaryCase1() || !testBoundaryCase2()) {
        printf("~ Tests have failed");
        return RETURN_TESTS_FAILED;
    }
    size_t size = 0;
    printf("Enter array size: ");
    fgets(&size, sizeof(size_t), stdin);
    size = atoi(&size);

    int* const numbers = (int*)malloc(sizeof(int) * size);
    if (numbers == NULL) 
    {
        printf("Memory allocation has failed");
        return RETURN_OUT_OF_MEMORY;
    }

    for (size_t i = 0; i < size; ++i) 
    {
        printf("a[%d] = ", (int)i);
        fgets(&numbers[i], sizeof(int) + 1, stdin);
        numbers[i] = atoi(&numbers[i]);
    }

    shellSort(numbers, size);
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", numbers[i]);
    }

    free(numbers);
    return RETURN_OK;
}
