#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Date.h"
#include "Time.h"
#include "SensorType.h"
#include "LinkedList.h"



#ifndef OBSERVATION_H_INCLUDED
#define OBSERVATION_H_INCLUDED

struct Observation
{
    Date date;
    Time time;
    char* building;
    char* stair;
    char* room;
    char* sensorID;
    SensorType* sensorType;
    float observedValue;  

};
typedef struct Observation Observation;

/**
 * read a file and put the results in a LinkedKist.
 */
LinkedList* readFromFile(char* filepath);

/**
 * Reads a string representing an observation and returns a pointer to it  .
 */
Observation* readFromStream(char* stream);


/**
 * Print all obervations stored in a LinkedList  .
 */
void printObs(LinkedList* l);

/**
 * concatenates two strings by putting "_" in the middle.
 */

char* concatString(char* str1, char* str2);


#endif // OBSERVATION_H_INCLUDED