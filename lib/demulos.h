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
int selectStars(const struct star *firstData, const struct star *secondData, int firstDataSize, int secondDataSize, double parameters[], int idStars[]);
int starsCloseTogether(const struct star *firstStar, const struct star *secondStar, double seeing);
int separatedMagnitudesOfStars(const struct star *firstStar, const struct star *secondStar, double minDifferenceMagnitude);
double realDistanceBetweenStars(const struct star *firstStar, const struct star *secondStar);
double radiusOfAreaAroundStar(const struct star *singleStar, double parameters[]);

#endif
