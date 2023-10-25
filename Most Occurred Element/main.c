#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEGATIVE_SIZE -1
#define OK 0

int compareIntegers(const void* a, const void* b) 
{
    int* x = a;
    int* y = b;
    return *x - *y;
}

int printMostOccurredElement(int* const numbers, size_t size) 
{
    if (!size) 
    {
        printf("~ Got an empty array");
        return;
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
        }
        else 
        {
            currentElement = numbers[i];
            currentCount = 1;
        }

        if (currentCount > maxCount) 
        {
            maxCount = currentCount;
            mostOccurredElement = currentElement;
        }
    }

    printf("* Most occurred integer: %d", mostOccurredElement);
}

int main() 
{
    size_t size = 0;

    printf("> Enter array size: ");
    fgets(&size, sizeof(size_t) + 1, stdin);
    size = atoi(&size);

    if (size < 0) 
    {
        printf("!! Array size can not be negative !!");
        return NEGATIVE_SIZE;
    }

    int* const numbers = (int*)malloc(size * sizeof(int));
    for (size_t i = 0; i < size; ++i)
    {
        printf("> a[%d] = ", i);
        fgets(&numbers[i], sizeof(int) + 1, stdin);
        numbers[i] = atoi(&numbers[i]);
    }

    printMostOccurredElement(numbers, size);
    free(numbers);

    return OK;
}
