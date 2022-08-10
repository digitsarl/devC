#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED


struct Date
{
    int year;
    int month;
    int day;
};
typedef struct Date Date;

#endif // DATE_H_INCLUDED