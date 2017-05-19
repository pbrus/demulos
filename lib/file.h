#ifndef _BRUS_FILE_
#define _BRUS_FILE_

/*
 * Simple library to handle text files
 * Przemysław Bruś
 * https://github.com/pbrus/
 *
 * ver. 2017-05-19
 */

FILE *getFileDescriptor(char *filename, char *mode);
int amountOfLinesInFile(FILE *fileDescriptor, int *sizeOfLongestLine);

#endif
