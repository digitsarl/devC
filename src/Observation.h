#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Date.h"
#include "Time.h"
#include "SensorType.h"
#include "LinkedList.h"
#include "Utils.h"

#include "serd/serd.h"
#include "sord/sord.h"
#include "sord_internal.h"

#include "zix/digest.h"

//#include "sord_test.c"



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
 * Free an observation object  .
 */
void freeObservation(Observation* obs);

/**
 * Print all obervations stored in a LinkedList  .
 */
void printObs(LinkedList* l);


/**
 * get the subject (as a string) from an observation.
 */
char* getSubject(Observation* obs);

/**
 * get the object (as a string) from an observation.
 */
char* getObject(Observation* obs, char* predicate);

/**
 * get the sensorType object (as a string) from an observation.
 */
char* getObjectSensorType(Observation* obs);

/**
 * get more information about the sensorType (as a string) from an observation.
 */
char* getObjectMoreSensorType(Observation* obs);

/**
 * get the date and time object (as a string) from an observation.
 */
char* getObjectDateTime(Observation* obs);

/**
 * get more information about the date and time (as a string) from an observation.
 */
char* getObjectMoreDateTime(Observation* obs);


/**
 * get the observedValue object (as a string) from an observation.
 */
char* getObjectObservedValue(Observation* obs);

/**
 * get the building, stair, room, sensorID and sensorType object (as a string) from an observation.
 */
char* getObjectOther(Observation* obs);

/**
 * get the date and time attributes (as a string) from an observation.
 */
char* getTimesAttr(Observation* obs);

/**
 * get the building, stair and room attributes (as a string) from an observation.
 */
char* getAttr(Observation* obs);



void test(char* initialFactFilePath);



#endif // OBSERVATION_H_INCLUDED