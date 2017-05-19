#ifndef _DEMULOS_DEMULOS_H_
#define _DEMULOS_DEMULOS_H_

struct star
{
    int id;
    double xCoordinate;
    double yCoordinate;
    double magnitude;
};

int setSmallerIntegerValue(int firstValue, int secondValue);
int readInputFile(FILE *fileDescriptor, struct star *dataPointer);
void fillOutputTableWithDataIds(const struct star *data, int outputTableIds[], int dataSize);
void selectStars(const struct star *firstDataSet, const struct star *secondDataSet, int firstDataSize, int secondDataSize, double parameters[], int idStars[]);
int starsCloseTogether(const struct star *firstStar, const struct star *secondStar, double seeing);
int separatedMagnitudesOfStars(const struct star *firstStar, const struct star *secondStar, double minDifferenceMagnitudes);
double realDistanceBetweenStars(const struct star *firstStar, const struct star *secondStar);
double radiusOfAreaAroundStar(const struct star *singleStar, double parameters[]);
void printOutput(const struct star *data, int outputTableIds[], int dataSize);

#endif
