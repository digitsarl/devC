#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

/**
 * Structure repesenting the date attribute of an observation's instance.
 */
struct Date
{
    /**
	 *year of the observation.
	 */
    int year;

    /**
	 *month of the observation.
	 */
    int month;

    /**
	 *day of the observation.
	 */
    int day;
};
typedef struct Date Date;

#endif // DATE_H_INCLUDED