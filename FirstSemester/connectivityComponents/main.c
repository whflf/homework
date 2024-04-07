#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "connectedComponents.h"

int main(void)
{
    int incidenceMatrix[5][6] = { 
        {1, 1, 1, 0, 1, 0}, 
        {1, 0, 0, 1, 0, 0}, 
        {0, 1, 0, 0, 0, 1}, 
        {0, 0, 1, 0, 0, 1}, 
        {0, 0, 0, 1, 1, 0} };

    printComponents(incidenceMatrix, 5);
}
