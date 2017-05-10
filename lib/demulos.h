#ifndef _DEMULOS_DEMULOS_H_
#define _DEMULOS_DEMULOS_H_

struct star
{
    int id;
    double xCoordinate;
    double yCoordinate;
    double magnitude;
};

int setGreaterIntegerValue(int firstValue, int secondValue);
void readInputFile(FILE *fileDescriptor, struct star *dataPointer);

#endif
