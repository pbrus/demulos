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

void displayHelp(double parameters[])
{
    printf("This program gets two lists with stars and returns the first list removing stars which are contaminated by stars from the second list. ");
    printf("The first list should contain preselected stars to the PSF model. The second list represents all stars found on an image. ");
    printf("Both lists should have the following structure:\n\n");
    printf(" # ID_star Xpx Ypx Mag\n\n");
    printf("ID_star is converted into integer, the rest of columns is treated as float numbers.\n");
    printf("Usage:\n\n %s <list-1> <list-2> [--seeing float] [--diff-mag float] [--max-mag float]\n\nOptions:\n\n", PROG);
    printf(" --seeing   N\tThe value of seeing on the current image. It is used to calculate a modified\n");
    printf("             \tdistance between two stars (default: %.2lf)\n", parameters[0]);
    printf(" --diff-mag N\tThe difference of magnitudes between stars from the first and second lists\n");
    printf("             \tIf a real difference is smaller than this value it means that a star from\n");
    printf("             \tthe first list is contaminated by a star from the second list and will be\n");
    printf("             \tremoved - if stars are sufficient close (default: %.2lf)\n", parameters[1]);
    printf(" --max-mag  N\tThe value of the faintest (reliable) star on the image. It's used to calculate\n");
    printf("             \tthe modified distance between two stars (default: %.2lf)\n\n", parameters[2]);
    printf("An example of usage:\n\n demulos psf.lst stars.lst --max-mag 20.5 --seeing 6.70\n\n");
}

void displayVersion()
{
    printf("%s\n", PROG);
    printf(" * Version: 2017-05-19\n");
    printf(" * Licensed under the MIT license:\n   http://opensource.org/licenses/MIT\n");
    printf(" * Copyright (c) 2017 Przemysław Bruś\n");
}

void cannotAllocateMemory()
{
    printf("Error from %s: Cannot allocate memory\n", PROG);
}
