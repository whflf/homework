#include <stdlib.h>
#include <stdbool.h>
#include "qsort.h"

void swap(int* const value1, int* const value2)
{
    const int value1Prev = *value1;
    *value1 = *value2;
    *value2 = value1Prev;
}

void partition(int* const array, int* const left, int* const right)
{
    const int pivot = array[(*left + *right) / 2];
    do
    {
        while (array[*left] < pivot) ++*left;
        while (array[*right] > pivot) --*right;
        if (*left <= *right)
        {
            swap(&array[*left], &array[*right]);
            ++*left;
            --*right;
        }
    } while (*left <= *right);
}

void quicksort(int* const array, const int low, const int high)
{
    if (low >= high)
    {
        return;
    }

    int left = low, right = high;
    partition(array, &left, &right);
    quicksort(array, low, right);
    quicksort(array, left, high);
}
