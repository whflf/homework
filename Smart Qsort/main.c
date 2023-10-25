#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int scanfSafetyChecks(int scanfFieldsFilled)
{
    char* extraInput = { '\0' };

    if (!scanfFieldsFilled) {
        printf("!! Wrong input. Please enter an integer but nothing else !!");
        return 1;
    }
    if (scanf_s("%c", &extraInput) != EOF && extraInput != '\n') {
        printf("!! Extra characters found in input. Please enter an integer and nothing else !!");
        return 2;
    }
    return 0;
}

void swap(int* value1, int* value2)
{
    int value1Prev = *value1;
    *value1 = *value2;
    *value2 = value1Prev;
}

void insertionSort(int* array, int low, int high)
{
    for (int i = low; i <= high - 1; ++i) {
        if (i == low && low == 0) 
        {
            continue;
        }
        int j = i - 1;
        while (array[j + 1] < array[j]) {
            swap(&array[j + 1], &array[j]);
            --j;
        }
    }
}

int partition(int array[], int low, int high)
{
    int pivot = array[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (array[j] <= pivot) {
            ++i;
            if (i != j) {
                swap(&array[i], &array[j]);
            }
        }
    }

    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quicksort(int array[], int low, int high)
{
    if (low < high) {
        int partitionIndex = partition(array, low, high);
        if ((partitionIndex - low) >= 10) {
            quicksort(array, low, partitionIndex);
        }
        else {
            insertionSort(array, low, partitionIndex + 1);
        }
        if ((high - partitionIndex) >= 10) {
            quicksort(array, partitionIndex + 1, high);
        }
        else {
            insertionSort(array, partitionIndex, high + 1);
        }
    }
}

bool testCorrectCase()
{
    int unsortedArray[5] = { 2, 5, 4, 3, 1 };
    int sortedArray[5] = { 1, 2, 3, 4, 5 };
    quicksort(unsortedArray, 0, 4);
    return memcmp(unsortedArray, sortedArray, 5) == 0;
}

bool testBoundaryCase()
{
    int unsortedArray[5] = { 1, 2, 3, 4, 5 };
    int sortedArray[5] = { 1, 2, 3, 4, 5 };
    quicksort(unsortedArray, 0, 4);
    return memcmp(unsortedArray, sortedArray, 5) == 0;
}

int main() {
    if (!testCorrectCase() || !testBoundaryCase())
    {
        printf("~ Tests failed");
        return -1;
    }

    int size = 0;

    printf("> Enter array size: ");

    if (scanfSafetyChecks(scanf_s("%d", &size))) {
        return 1;
    }

    if (size < 0) {
        printf("!! Array size can not be negative !!");
        return 1;
    }

    int* numbers = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i)
    {
        printf("> a[%d] = ", i);

        if (scanfSafetyChecks(scanf_s("%d", &numbers[i]))) {
            return 1;
        }
    }

    quicksort(numbers, 0, size - 1);

    printf("Result: ");
    for (int i = 0; i < size; ++i) {
        printf("%d", numbers[i]);
        if (i < size - 1) {
            printf(",");
        }
    }
    printf("\n");

    free(numbers);
    return 0;
}