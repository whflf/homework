#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define BAD_INPUT 1
#define OUT_OF_MEMORY 2
#define TESTS_FAILED 3

#define countof(array) sizeof(array) / sizeof(array[0])

int compareIntegers(const void* a, const void* b)
{
    int* x = a;
    int* y = b;
    return *x - *y;
}

int getMostOccurredElement(int* const numbers, const size_t size)
{
    if (size == 1)
    {
        return numbers[0];
    }

    qsort(numbers, 0, size - 1, compareIntegers);

    int mostOccurredElement = numbers[0];
    int currentElement = numbers[0];
    int currentCount = 1;
    int maxCount = 1;

    for (size_t i = 1; i < size; ++i)
    {
        if (numbers[i] == currentElement)
        {
            ++currentCount;
            if (currentCount > maxCount)
            {
                maxCount = currentCount;
                mostOccurredElement = currentElement;
            }
        }
        else
        {
            currentElement = numbers[i];
            currentCount = 1;
        }
    }

    return mostOccurredElement;
}

char testCorrectCase(void)
{
    int array[] = { 1, 2, 3, 3, 4 };
    return getMostOccurredElement(array, countof(array)) == 3;
}

char testBoundaryCase(void)
{
    int array[] = { 1, 2, 3, 4, 5 };
    return getMostOccurredElement(array, countof(array)) == array[0];
}

int main(void)
{
    if (!testCorrectCase() && !testBoundaryCase())
    {
        printf("Tests failed.\n");
        return TESTS_FAILED;
    }

    size_t size = 0;

    printf("> Enter array size: ");

    if (!scanf("%zu", &size) || size == 0)
    {
        printf("Wrong input for array size. A non-zero positive integer required.\n");
        return BAD_INPUT;
    }

    int* const numbers = (int*)malloc(size * sizeof(int));

    if (!numbers)
    {
        printf("Memory allocation failed (size=%zu).\n", size);
        return OUT_OF_MEMORY;
    }

    for (size_t i = 0; i < size; ++i)
    {
        printf("> a[%zu] = ", i);
        if (!scanf("%d", &numbers[i]))
        {
            printf("Wrong input for a[%zu]. A valid integer required.\n", i);
            return BAD_INPUT;
        }
    }

    printf("Most occurred integer: %d\n", getMostOccurredElement(numbers, size));
    free(numbers);

    return OK;
}
