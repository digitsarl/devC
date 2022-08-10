#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED


struct Time
{
    int hour;
    int minute;
    int second;
};
typedef struct Time Time;

#endif // TIME_H_INCLUDED