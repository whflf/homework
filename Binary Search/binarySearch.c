#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define TEST_LENGTH 5

#define NOTHING_FOUND -1
#define OK 0
#define TESTS_FAILED 1
#define OUT_OF_MEMORY 2

int compare(const void* a, const void* b)
{
    int* x = a;
    int* y = b;
    return *x - *y;
}

int* randArray(const size_t n, const int rangeMax, const int rangeMin)
{
    int* const randomNumbers = (int*)malloc(n * sizeof(int));
    if (randomNumbers == NULL) 
    {
        return NULL;
    }
    else 
    {
        srand(time(NULL));
        for (size_t i = 0; i < n; ++i) {
            randomNumbers[i] = ((double)rand() / RAND_MAX) * (rangeMax - rangeMin) + rangeMin;
        }
    }

    return randomNumbers;
}

size_t binarySearch(int* const array, int first, int last, const int number)
{
    while (first <= last) 
    {
        size_t middle = first + (last - first) / 2;
        if (array[middle] == number) 
        {
            return middle;
        }
        if (array[middle] < number) 
        {
            first = middle + 1;
        }
        else 
        {
            last = middle - 1;
        }
    }

    return NOTHING_FOUND;
}

bool testCorrectCase()
{
    int testArray[TEST_LENGTH] = { 4, 9, 1, 0, 3 };
    qsort(testArray, TEST_LENGTH, sizeof(int), compare);
    return binarySearch(testArray, 0, 4, 0) != -1;
}

bool testIncorrectCase()
{
    int testArray[TEST_LENGTH] = { 4, 9, 1, 0, 3 };
    qsort(testArray, TEST_LENGTH, sizeof(int), compare);
    return binarySearch(testArray, 0, 4, 5) == -1;
}

int main() {
    if (!testCorrectCase() || !testIncorrectCase()) 
    {
        printf("~ Tests failed");
        return TESTS_FAILED;
    }

    size_t n = 0;
    size_t k = 0;

    printf("> n = ");
    scanf_s("%d", &n);

    int* const numbers = randArray(n, 0, 100);
    if (numbers == NULL) 
    {
        printf("Memory allocation has failed :(");
        return OUT_OF_MEMORY;
    }
    printf("Array of %d numbers: ", n);
    for (size_t i = 0; i < n; ++i) 
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    qsort(numbers, n, sizeof(int), compare);

    printf("Sorted array: ");
    for (size_t i = 0; i < n; ++i) 
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    printf("> k = ");
    scanf_s("%d", &k);

    for (size_t i = 0; i < k; ++i) 
    {
        const int key = ((double)rand() / RAND_MAX) * 50;
        const int index = binarySearch(numbers, 0, n - 1, key);
        if (index > -1) 
        {
            printf("%d is in the array\n", key);
        }
        else 
        {
            printf("%d is not in the array\n", key);
        }
    }

    free(numbers);
    return OK;
}
