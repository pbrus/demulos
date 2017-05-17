#ifndef PROG
#define PROG "demulos"
#endif

#include <stdio.h>

void displayBasicInfo()
{
    printf("\n %s => (de)lete (mul)tiple (o)bject(s)\n\n", PROG);
    printf(" Default call: \n  %s <star-list-1> <star-list-2>\n", PROG);
    printf(" For more info please type:\n  %s --help\n", PROG);
    printf(" Display version information and exit:\n  %s -v\n\n", PROG);
    printf(" Copyright (c) Przemysław Bruś\n\n");
}

void displayHelp()
{
    printf("This program gets two lists with stars and returns the first list removing stars which are contaminated by stars from the second list. ");
    printf("The first list should contain preselected stars to the PSF model. The second list represents all stars found on an image. ");
    printf("Both lists should have the following structure:\n\n");
    printf(" # ID_star Xpx Ypx Mag\n\n");
    printf("ID_star is converted into integer, the rest of columns is treated as float numbers.\n");
    printf("Usage:\n\n %s <list-1> <list-2> [--seeing float] [--diff-mag float] [--max-mag float]\n\nOptions:\n\n", PROG);
    printf("");
}

void displayVersion()
{
    printf("%s\n", PROG);
    printf(" * Version: 2017-05-17\n");
    printf(" * Licensed under the MIT license:\n   http://opensource.org/licenses/MIT\n");
    printf(" * Copyright (c) 2017 Przemysław Bruś\n");
}

void displayDefaultArgs(double *parameters)
{
    printf("Default values of arguments:\n");
    printf(" * seeing = %.2f\n", parameters[0]);
    printf(" * diff-mag = %.2f\n", parameters[1]);
    printf(" * max-mag = %.2f\n", parameters[2]);
}

void cannotAllocateMemory()
{
    printf("Cannot allocate memory\n");
}
