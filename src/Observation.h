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


#ifndef OBSERVATION_H_INCLUDED
#define OBSERVATION_H_INCLUDED

// ---------------------------------------------- Structures ---------------------------------------------------

/**
 * Structure representing an observation.
 */
struct Observation
{
    /**
     * Structure representing the date.
     */
    Date date;

    /**
     * Structure representing the time.
     */
    Time time;

    /**
     * It represents the name of the building .
     */
    char* building;

    /**
     * It represents the number of the floor .
     */
    char* stair;

    /**
     * It represents the number of the room .
     */
    char* room;

    /**
     * it represents the identifier of the sensor.
     */
    char* sensorID;

    /**
     * Structure representing the type of the sensor.
     */
    SensorType* sensorType;

     /**
     * it represents the observed value by the sensor.
     */
    float observedValue;  

};
typedef struct Observation Observation;

// ---------------------------------------------- Functions ---------------------------------------------------

/**
 * read a file and put the results (instances of observations) in a LinkedList.
 */
LinkedList* readFromFile(char* filepath);

/**
 * Reads a string representing an observation and returns a pointer to it  .
 */
Observation* readFromStream(char* stream);

/**
 *Frees the memory space allocated to the observation's instance.
 */
void freeObservation(Observation* obs);

/**
 * Display in console all obervations stored in a LinkedList  .
 */
void printObs(LinkedList* l);

/**
 * get the subject (as a string) from an observation.
 */
char* getSubject(Observation* obs);

/**
 * get the object (as a string) from an observation.
 * @param predicate is a predicate (as a string) of a fact.
 */
char* getObject(Observation* obs, char* predicate);

/**
 * get the object (as a string) referring to the sensorType attribute from an observation.
 */
char* getObjectSensorType(Observation* obs);

/**
 * get the object (as a string) referring to more information about the sensorType from an observation.
 */
char* getObjectMoreSensorType(Observation* obs);

/**
 * get the object (as a string) referring to date and time attributes from an observation.
 */
char* getObjectDateTime(Observation* obs);

/**
 * get the object (as a string) referring to more information about the date and time from an observation.
 */
char* getObjectMoreDateTime(Observation* obs);

/**
 * get object (as a string) referring to the observedValue attribute from an observation.
 * This object (as a string) will be converted to a literal SordNode later 
 */
char* getObjectObservedValue(Observation* obs);

/**
 * get the object (as a string) referring to the building, stair, room, sensorID and sensorType attributes from an observation.
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

/**
 * get the sensorID attribute (as a string) from an observation.
 */
char* getSensorID(Observation* obs);




#endif // OBSERVATION_H_INCLUDED