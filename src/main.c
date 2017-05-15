#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include "../lib/comm.h"
#include "../lib/file.h"
#include "../lib/demulos.h"


int main(int argc, char *argv[])
{
    int argParser;
    double optionalParameters[] = {5., 3., 20.};

    while (1)
    {
        static struct option long_options[] =
        {
            {"seeing", required_argument, 0, 's'},
            {"diff-mag", required_argument, 0, 'd'},
            {"max-mag", required_argument, 0, 'm'},
            {0, 0, 0, 0},
        };

        int option_index = 0;
        argParser = getopt_long(argc, argv, "s:d:m:", long_options, &option_index);

        if (argParser == -1)
        {
            break;
        }

        switch (argParser)
        {
            case 's':
                optionalParameters[0] = atof(optarg);
                break;

            case 'd':
                optionalParameters[1] = atof(optarg);
                break;

            case 'm':
                optionalParameters[2] = atof(optarg);
                break;

            case '?':
                break;

            default:
            abort();
        }
    }

    FILE *firstFileDescriptor, *secondFileDescriptor;

    if (optind % 2 == 0)
    {
        exit(0);
    }
    else if ((argc - optind) != 2)
    {
        info();
        exit(0);
    }
    else
    {
        firstFileDescriptor = getFileDescriptor(argv[argc-2], "r");
        secondFileDescriptor = getFileDescriptor(argv[argc-1], "r");

        if (firstFileDescriptor == NULL || secondFileDescriptor == NULL)
        {
            exit(0);
        }
    }

    int sizeOfFirstFile, sizeOfSecondFile, temporaryInt;
    struct star *firstData, *secondData;

    sizeOfFirstFile = amountOfLinesInFile(firstFileDescriptor, &temporaryInt);
    sizeOfSecondFile = amountOfLinesInFile(secondFileDescriptor, &temporaryInt);

    firstData = malloc(sizeOfFirstFile * sizeof(struct star));
    secondData = malloc(sizeOfSecondFile * sizeof(struct star));

    if (firstData == NULL || secondData == NULL)
    {
        cannotAllocateMemory();
        exit(0);
    }

    int maxSizeOfOutputData, *tableForOutputIds;

    maxSizeOfOutputData = setSmallerIntegerValue(sizeOfFirstFile, sizeOfSecondFile);
    tableForOutputIds = malloc(maxSizeOfOutputData * sizeof(int));

    if (tableForOutputIds == NULL)
    {
        cannotAllocateMemory();
        exit(0);
    }

    int firstDataSize, secondDataSize;

    firstDataSize = readInputFile(firstFileDescriptor, firstData);
    secondDataSize = readInputFile(secondFileDescriptor, secondData);

    fclose(firstFileDescriptor);
    fclose(secondFileDescriptor);


    free(firstData);
    free(secondData);
    free(tableForOutputIds);
}
