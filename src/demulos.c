#include <stdio.h>
#include <math.h>
#include "../lib/demulos.h"

int setSmallerIntegerValue(int firstValue, int secondValue)
{
    int smallerValue;

    if (firstValue < secondValue)
    {
        smallerValue = firstValue;
    }
    else
    {
        smallerValue = secondValue;
    }

    return smallerValue;
}

int readInputFile(FILE *fileDescriptor, struct star *dataPointer)
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

    return i;
}

void fillOutputTableWithDataIds(const struct star *data, int outputTableIds[], int dataSize)
{
    int iterator;

    for (iterator = 0; iterator < dataSize; iterator++)
    {
        outputTableIds[iterator] = (data + iterator)->id;
    }
}

int selectStars(const struct star *firstData, const struct star *secondData, int firstDataSize, int secondDataSize, double parameters[], int idStars[])
{
    int firstIterator, secondIterator, returnedStarsIterator, closeStars, separatedMagnitudes;
    double seeing = parameters[0], minDifferenceMagnitudes = parameters[1];
    double realDistance, radiusAroundStar;

    for (firstIterator = 0; firstIterator < firstDataSize; firstIterator++)
    {
        for (secondIterator = 0; secondIterator < secondDataSize; secondIterator++)
        {
            closeStars = starsCloseTogether(firstData + firstIterator, secondData + secondIterator, seeing);

            if (closeStars)
            {
                separatedMagnitudes = separatedMagnitudesOfStars(firstData + firstIterator, secondData + secondIterator, minDifferenceMagnitudes);

                if (separatedMagnitudes)
                {
                    continue;
                }
                else
                {
                    realDistance = realDistanceBetweenStars(firstData + firstIterator, secondData + secondIterator);
                    radiusAroundStar = radiusOfAreaAroundStar(firstData + firstIterator, parameters);

                    if (realDistance >= radiusAroundStar)
                    {
                        continue;
                    }
                    else
                    {
                        idStars[firstIterator] = -1;
                        break;
                    }
                }
            }
        }
    }

    return returnedStarsIterator;
}

int starsCloseTogether(const struct star *firstStar, const struct star *secondStar, double seeing)
{
    int starsCloseTogether = 0;
    double initialSeeingMultiplier = 10.0;

    if (firstStar->id != secondStar->id)
    {
        if (fabs(firstStar->xCoordinate - secondStar->xCoordinate) < initialSeeingMultiplier * seeing)
        {
            if (fabs(firstStar->yCoordinate - secondStar->yCoordinate) < initialSeeingMultiplier * seeing)
            {
                starsCloseTogether = 1;
            }
        }
    }

    return starsCloseTogether;
}

int separatedMagnitudesOfStars(const struct star *firstStar, const struct star *secondStar, double minDifferenceMagnitudes)
{
    int separatedMagnitudes = 0;
    double differenceMagnitudes;

    differenceMagnitudes = firstStar->magnitude - secondStar->magnitude;
    differenceMagnitudes *= -1.0;

    if (differenceMagnitudes > minDifferenceMagnitudes)
    {
        separatedMagnitudes = 1;
    }

    return separatedMagnitudes;
}

double realDistanceBetweenStars(const struct star *firstStar, const struct star *secondStar)
{
    double distance, deltaX, deltaY;

    deltaX = firstStar->xCoordinate - secondStar->xCoordinate;
    deltaY = firstStar->yCoordinate - secondStar->yCoordinate;

    distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

    return distance;
}

double radiusOfAreaAroundStar(const struct star *singleStar, double parameters[])
{
    double seeing = parameters[0], differenceMagnitudes = parameters[1], maxMagnitude = parameters[2];
    double radius;

    radius = 2.0 * seeing * ((maxMagnitude - singleStar->magnitude) / 4.0 + 0.5);

    return radius;
}

void writeOutputToFile(const struct star *data, int outputTableIds[], int dataSize)
{
    int iterator;
    FILE *fileDescriptor;

    fileDescriptor = fopen("demulos.out", "w");

    for (iterator = 0; iterator < dataSize; iterator++)
    {
        if (outputTableIds[iterator] != -1)
        {
            fprintf(fileDescriptor, "%8d %10.3lf %10.3lf %8.3lf\n", (data + iterator)->id, (data + iterator)->xCoordinate, (data + iterator)->yCoordinate, (data + iterator)->magnitude);
        }
    }
}
