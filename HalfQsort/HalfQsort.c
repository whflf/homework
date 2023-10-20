#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#define RAND_ARRAY_LENGTH 20
#define OK 0
#define NEGATIVE_NUMBER_ERROR -1
#define OUT_OF_MEMORY 1
#define TESTS_FAILED 2

void swap(int* value1, int* value2)
{
    int value1Prev = *value1;
    *value1 = *value2;
    *value2 = value1Prev;
}

void halfQsort(int* array, size_t size)
{
    int index = 0;
    int firstElement = array[0];

    for (int i = 1; i < size; ++i) 
    {
        if (array[i] < firstElement) 
        {
            swap(&array[i], &array[index++]);
        }
    }
}

int* randArray()
{
    int* const randomNumbers = (int*)malloc(RAND_ARRAY_LENGTH * sizeof(int));

    if (randomNumbers == NULL) 
    {
        int randomNumbers[1] = { -1 };
    }
    else 
    {
        srand(time(NULL));
        for (int i = 0; i < RAND_ARRAY_LENGTH; ++i) 
        {
            randomNumbers[i] = rand();
        }
    }

    return randomNumbers;
}

bool testCorrectCase()
{
    int array1[5] = { 3, 1, 4, 5, 2 };
    int array2[5] = { 1, 2, 4, 5, 3 };

    halfQsort(array1, 5);

    return memcmp(array1, array2, 5) == 0;
}

bool testBoundaryCase1()
{
    int array1[5] = { 1, 2, 3, 4, 5 };
    int array2[5] = { 1, 2, 3, 4, 5 };

    halfQsort(array1, 5);

    return memcmp(array1, array2, 5) == 0;
}

bool testBoundaryCase2()
{
    int array1[5] = { 5, 4, 3, 2, 1 };
    int array2[5] = { 4, 3, 2, 1, 5 };

    halfQsort(array1, 5);

    return memcmp(array1, array2, 5) == 0;
}

int main()
{
    if (!testCorrectCase() || !testBoundaryCase1() || !testBoundaryCase2()) 
    {
        printf("Tests failed :(");
        return TESTS_FAILED;
    }

    int* numbers = randArray();
    int memoryErrorArray[1] = { -1 };
    if (memcmp(numbers, memoryErrorArray, 1) == 0) 
    {
        printf("~ Memory allocation has failed");
        return OUT_OF_MEMORY;
    }

    printf("Before conversion: ");
    for (int i = 0; i < 20; ++i) 
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    halfQsort(numbers, RAND_ARRAY_LENGTH);
    printf("After conversion: ");
    for (int i = 0; i < RAND_ARRAY_LENGTH; ++i) 
    {
        printf("%d ", numbers[i]);
    }

    free(numbers);
    return OK;
}