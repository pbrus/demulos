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
            {"help", no_argument, 0, 'h'},
            {"version", no_argument, 0, 'v'},
            {0, 0, 0, 0},
        };

        int option_index = 0;
        argParser = getopt_long(argc, argv, "s:d:m:hv", long_options, &option_index);

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

            case 'h':
                displayHelp();
                exit(0);

            case 'v':
                displayVersion();
                exit(0);

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
        displayBasicInfo();
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

    int firstDataSize, secondDataSize, temporaryInt;
    struct star *firstDataSet, *secondDataSet;

    firstDataSize = amountOfLinesInFile(firstFileDescriptor, &temporaryInt);
    secondDataSize = amountOfLinesInFile(secondFileDescriptor, &temporaryInt);

    firstDataSet = malloc(firstDataSize * sizeof(struct star));
    secondDataSet = malloc(secondDataSize * sizeof(struct star));

    if (firstDataSet == NULL || secondDataSet == NULL)
    {
        cannotAllocateMemory();
        exit(0);
    }

    int maxSizeOfOutputData, *tableForOutputIds;

    maxSizeOfOutputData = setSmallerIntegerValue(firstDataSize, secondDataSize);
    tableForOutputIds = malloc(maxSizeOfOutputData * sizeof(int));

    if (tableForOutputIds == NULL)
    {
        cannotAllocateMemory();
        exit(0);
    }

    readInputFile(firstFileDescriptor, firstDataSet);
    readInputFile(secondFileDescriptor, secondDataSet);
    fclose(firstFileDescriptor);
    fclose(secondFileDescriptor);

    fillOutputTableWithDataIds(firstDataSet, tableForOutputIds, firstDataSize);
    selectStars(firstDataSet, secondDataSet, firstDataSize, secondDataSize, optionalParameters, tableForOutputIds);
    writeOutputToFile(firstDataSet, tableForOutputIds, firstDataSize);

    free(firstDataSet);
    free(secondDataSet);
    free(tableForOutputIds);
}
