#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

/**
 * Structure repesenting the time attribute of an observation's instance.
 */
struct Time
{
    /**
	 *hour of the observation.
	 */
    int hour;

    /**
	 *number of minute of the observation.
	 */
    int minute;

    /**
	 *number of seconde of the observation.
	 */
    int second;
};
typedef struct Time Time;

#endif // TIME_H_INCLUDED