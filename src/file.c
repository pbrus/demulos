#include <stdio.h>

FILE *getFileDescriptor(char *filename, char *mode)
{
    FILE *fileDescriptor = fopen(filename, mode);

    if (fileDescriptor == NULL)
    {
        printf("Cannot open %s file\n", filename);
    }

    return fileDescriptor;
}

int amountOfLinesInFile(FILE *fileDescriptor, int *sizeOfLongestLine)
{
    int amountOfLines = 0, temporarySizeOfLine = 0;
    char singleChar;

    *sizeOfLongestLine = 0;

    do
    {
        singleChar = fgetc(fileDescriptor);
        temporarySizeOfLine++;

        if (singleChar == '\n')
        {
            amountOfLines++;

            if (temporarySizeOfLine > *sizeOfLongestLine)
            {
                *sizeOfLongestLine = temporarySizeOfLine;
            }

            temporarySizeOfLine = 0;
        }
    }
    while (singleChar != EOF);

    *sizeOfLongestLine += 1;
    rewind(fileDescriptor);

    return amountOfLines;
}
