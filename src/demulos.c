#include <stdio.h>
#include "../lib/demulos.h"

int setGreaterIntegerValue(int firstValue, int secondValue)
{
    int maxSize;

    if (firstValue < secondValue)
    {
        maxSize = firstValue;
    }
    else
    {
        maxSize = secondValue;
    }

    return maxSize;
}

void readInputFile(FILE *fileDescriptor, struct star *dataPointer)
{
    int i = 0;

    while (1)
    {
        if (fscanf(fileDescriptor, "%d %lf %lf %lf", &((dataPointer + i)->id), &((dataPointer + i)->xCoordinate), &((dataPointer + i)->yCoordinate), &((dataPointer + i)->magnitude)) != 4)
        {
            break;
        }

        i++;
    }

    rewind(fileDescriptor);
}
