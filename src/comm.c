#ifndef PROG
#define PROG "demulos"
#endif

#include <stdio.h>

void displayDefaultArgs(double *parameters)
{
    printf("Default values of arguments:\n");
    printf(" * seeing = %.2f\n", parameters[0]);
    printf(" * diff-mag = %.2f\n", parameters[1]);
    printf(" * max-mag = %.2f\n", parameters[2]);
}

void info()
{
    printf("\n %s => (de)lete (mul)tiple (o)bject(s)\n\n", PROG);
    printf(" Default call: \n  %s <star-list-1> <star-list-2>\n", PROG);
    printf(" For more info please type:\n  %s --help\n", PROG);
    printf(" Display version information and exit:\n  %s -v\n\n", PROG);
    printf(" Copyright (c) Przemysław Bruś\n\n");
}

void version()
{
    printf("%s\n", PROG);
}

void cannotAllocateMemory()
{
    printf("Cannot allocate memory\n");
}
