#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define TEST_LENGTH 5
#define RANDOM_MAX 100
#define KEY_MULTIPLIER 50

#define NOT_FOUND -1
#define OK 0
#define TESTS_FAILED 1
#define OUT_OF_MEMORY 2

int compare(const void* a, const void* b)
{
    const int* x = a;
    const int* y = b;
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
        for (size_t i = 0; i < n; ++i) 
        {
            randomNumbers[i] = (int)(((double)rand() / RAND_MAX) * (rangeMax - rangeMin) + rangeMin);
        }
    }

    return randomNumbers;
}

size_t binarySearch(int* const array, size_t first, size_t last, const int number)
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

    return NOT_FOUND;
}

bool testCorrectCase()
{
    int testArray[TEST_LENGTH] = { 4, 9, 1, 0, 3 };
    qsort(testArray, TEST_LENGTH, sizeof(int), compare);
    return binarySearch(testArray, 0, 4, 0) != NOT_FOUND;
}

bool testIncorrectCase()
{
    int testArray[TEST_LENGTH] = { 4, 9, 1, 0, 3 };
    qsort(testArray, TEST_LENGTH, sizeof(int), compare);
    return binarySearch(testArray, 0, 4, 5) == NOT_FOUND;
}

int main(int argc, char* argv[])
{
    if (argc > 1 && strcmp(argv[1], "run tests") == 0)
    {
        return testCorrectCase() && testIncorrectCase();
    }

    if (!testCorrectCase() || !testIncorrectCase()) 
    {
        printf("~ Tests failed");
        return TESTS_FAILED;
    }

    size_t n = 0;
    size_t k = 0;

    printf("> n = ");
    scanf("%ld", &n);

    int* const numbers = randArray(n, RANDOM_MAX, 0);
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
    scanf("%ld", &k);

    for (size_t i = 0; i < k; ++i) 
    {
        const int key = (const int)(((double)rand() / RAND_MAX) * KEY_MULTIPLIER);
        const int index = binarySearch(numbers, 0, n - 1, key);
        if (index > NOT_FOUND) 
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
