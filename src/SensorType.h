#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SENSORTYPE_H_INCLUDED
#define SENSORTYPE_H_INCLUDED

/**
 * Structure repesenting the SensorType attribute of an observation's instance.
 */
enum SensorType
{
    Luminosity,
    Temperature,
    Humidity
};
typedef enum SensorType SensorType;

#endif // SENSORTYPE_H_INCLUDED