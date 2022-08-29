#include "Observation.h"
#define TAILLE_MAX 200

// ----------------------------------- Observations ----------------------------------------------------

LinkedList* readFromFile(char* filepath)   
{
    FILE *file = NULL;
    char valChar;
    LinkedList* l = createLinkedList();
    Observation* obs;

    char* stream = malloc(TAILLE_MAX * sizeof(char));
    file = fopen(filepath, "r");

    if (file != NULL)
    {
        while (fgets(stream, TAILLE_MAX, file) != NULL)
        {
            if(strlen(stream) > 1)
            {
                char* badStr1 = NULL; 
                char* badStr2 = NULL;

                // Check if a stream contains "itm-factory" or "mobile3"
                badStr1 = strstr(stream, "itm-factory"); 
                badStr2 = strstr(stream, "mobile3");
                if (!badStr1 && !badStr2)
                {
                    obs = readFromStream(stream);
                    insertInLast(l ,obs);
                }
            }
            
        }
        fclose(file);

        //free the stream
        free(stream);
       
    }
    else
    {
        printf("Cannot open file");
        free(stream);
    }
    return l;
}

Observation* readFromStream(char* stream)
{
    // 2022/03/23 19:14:16 emse/fayol/e4/S405/sensors/6bd134b6-339c-4168-9aeb-ae7d0f236851/metrics/LUMI 3
    // ------------------------------------------------OR--------------------------------------------------
    // 2022/03/23 19:15:20 emse/fayol/3ET/325/TEMP/outside 13.36

    // Verify is stream is an observation of an externe temperature
    char* resp = NULL;
    resp = strstr(stream, "sensors");
    

    // Create a static table to store the stream
    int lenStream = strlen(stream);
    char stream2[lenStream];
    for(int k=0;k<lenStream;k++)
    {
        stream2[k] = stream[k];
    }

    // Create a matrix of char to store trhe differents tokens of stream
    char ** matObser = malloc(15 * sizeof(char *));
    int i,j;

   // Extract the first token
   char * token = strtok(stream2, "/");
   

   // Store the first token
   matObser[0] = token;

   //Extract and store others tokens
   token = strtok(NULL, "/");
   matObser[1] = token;
   token = strtok(NULL, " ");
   matObser[2] = token;
   for( i=3; i<=4;i++)
   {
       token = strtok(NULL, ":");
       matObser[i] = token;
   }
   token = strtok(NULL, " ");
   matObser[i] = token;

   if(resp)
   {
       for(j=i+1; j<=i+7;j++)
       {
            token = strtok(NULL, "/");
            matObser[j] = malloc((strlen(token)+1)* sizeof(char)) ; 
            strcpy(matObser[j],token );
       }
   }
   else
   {
       for(j=i+1; j<=i+5;j++)
       {
            token = strtok(NULL, "/");
            matObser[j] = malloc((strlen(token)+1)* sizeof(char)) ; 
            strcpy(matObser[j],token );
       }
   } 
   
   token = strtok(NULL, " ");
   matObser[j] = malloc((strlen(token)+1)* sizeof(char)) ; 
   strcpy(matObser[j],token );

   token = strtok(NULL, " ");
   matObser[j+1] = malloc((strlen(token)+1)* sizeof(char)) ; 
   strcpy(matObser[j+1],token );

   // Construction of a Date object 
   Date date;
   date.year = atoi(matObser[0]);
   date.month = atoi(matObser[1]);
   date.day = atoi(matObser[2]); 

   // Construction of a Time object
   Time time;
   time.hour = atoi(matObser[3]);
   time.minute = atoi(matObser[4]);
   time.second = atoi(matObser[5]);

   // Attribute building
   char* elem = malloc(1 * sizeof(char));
   elem[0] = '_';
   char* building = concatString(matObser[6], matObser[7], elem);

        //free the two elements which contained the constitute elements of the building attribute
        free(matObser[6]);
        free(matObser[7]); 

        //free the string "elem"
        free(elem);

   // Attribute stair
   char* stair = matObser[8];

   // Attribute room
   char* room = matObser[9];

   // Attribute sensorID
   char* sensorID = NULL;
   if(resp)
   {
       sensorID = matObser[11];
   }
  
   // Attribute sensorType
   
    SensorType* sensorTypePointer  = malloc(sizeof(SensorType));
   if(resp)
   {
       if(strcmp(matObser[13], "LUMI") == 0)
       {
            (* sensorTypePointer) = Luminosity;
       }
       else if (strcmp(matObser[13], "TEMP") == 0)
       {
            (* sensorTypePointer) = Temperature;
       }
       else if (strcmp(matObser[13], "HMDT") == 0)
       {
            (* sensorTypePointer) = Humidity;
       }
        free(matObser[13]);
   }
   else
   {
       if(strcmp(matObser[10], "LUMI") == 0)
       {
            (* sensorTypePointer) = Luminosity;
       }
       else if (strcmp(matObser[10], "TEMP") == 0)
       {
            (* sensorTypePointer) = Temperature;
       }
       else if (strcmp(matObser[10], "HMDT") == 0)
       {
            (* sensorTypePointer) = Humidity;
       }
       free(matObser[10]);
   }
   
   // Attribute observedValue
   float observedValue;
   if(resp)
   {
       observedValue = atof(matObser[14]);
       free(matObser[14]);
   }
   else
   {
       observedValue = atof(matObser[12]);
       free(matObser[12]);
   } 
   

   // Construction of Observation
   Observation* observation  = malloc(sizeof(Observation)); //Instance

   (*observation).date = date;
   (*observation).time = time;
   (*observation).building = building;
   (*observation).stair = stair;
   (*observation).room = roomParse(room);
   (*observation).sensorID = sensorID;
   (*observation).sensorType = sensorTypePointer;
   (*observation).observedValue = observedValue;

   return observation;

}

void freeObservation(Observation* obs)
{
    free(obs->building);
    free(obs->room);
    free(obs->stair);
    free(obs->sensorID);
    free(obs->sensorType);
}

void printObs(LinkedList* l)
{
    printf("\n\n*************************print of Observations :******************************\n\n");
    int lenList = l->size;
    for(int i=0; i<lenList;i++)
    {
        printf("\n--------Observation ---------> %d : \n",i+1);
        printf("         ---------\n ");
        Observation* obs = getLinkedListAtIndex(l,i);

        SensorType* SensorTypePointer = (*obs).sensorType;
        
        printf("date : %d/%d/%d \n", (*obs).date.year, (*obs).date.month, (*obs).date.day);
        printf(" time : %d:%d:%d \n", (*obs).time.hour, (*obs).time.minute, (*obs).time.second);
        printf(" building : %s\n", (*obs).building);
        printf(" stair : %s\n", (*obs).stair);
        printf(" room : %s\n", (*obs).room);
        
        if((*obs).sensorID)
        {
            printf(" sensorID : %s\n", (*obs).sensorID);
        }
        
        if(*SensorTypePointer == 0)
        {
            printf(" sensorType : Luminosity \n");
        }
        else if (*SensorTypePointer == 1)
        {
            printf(" sensorType : Temperature \n");
        }
        else if (*SensorTypePointer == 2)
        {
            printf(" sensorType : Humidity \n");
        }
            
        printf(" observedValue  : %f\n\n", (*obs).observedValue);
    }

}

char* getSubject(Observation* obs)
{
    //**http://example.org/id/observation/emse_fauriel_3ET_460_Humidity_2022-03-23T19:14:16

    char init[50] = "http://example.org/id/observation";
    
    char sensorType1[20] = "Luminosity";
    char sensorType2[20] = "Temperature";
    char sensorType3[20] = "Humidity";

    char* elem = malloc(1 * sizeof(char));
    char* res = calloc(70,sizeof(char));
    char* buidingStairRoom = getAttr(obs);
    char* dateTime = getTimesAttr(obs);
    

    elem[0] = '/';
    res = concatString(init,buidingStairRoom,elem);

    elem[0] = '_';
    if( *(obs->sensorType) == 0 )
    {
        res = concatString(res,sensorType1,elem);
    }
    else if ( *(obs->sensorType) == 1 )
    {
        res = concatString(res,sensorType2,elem);
    }
    else if ( *(obs->sensorType) == 2 )
    {
        res = concatString(res,sensorType3,elem);
    }

    elem[0] = '_';
    res = concatString(res,dateTime,elem);
    
    return res;
}

char* getObject(Observation* obs, char* predicate)
{
    //  http://www.w3.org/1999/02/22-rdf-syntax-ns#type     **predicate for sensorType
    //  objExple: https://coswot.gitlab.io/ontology#LuminosityObservation


    //  http://www.w3.org/ns/sosa/observedProperty          **predicate for more information about sensortype
    //  objExple: http://example.org/id/property/emse_fauriel_4ET_405_sample1_ambientTemperatureProperty


    //  http://www.w3.org/ns/sosa/phenomenonTime            **predicate for date and time
    //  objExple: http://example.org/id/instant/2022-03-23T19:14:16


    //  http://www.w3.org/ns/sosa/resultTime                 **predicate for more information about date and Time
    //  objExple:  "2022-03-23T19:14:16Z"^^xsd:dateTime 
    

    //  http://www.w3.org/ns/sosa/madeBySensor              **predicate for building, stair, room, sensorID and sensorType
    //  objExple: http://example.org/id/sensor/emse_fauriel_4ET_405_6bd134b6-339c-4168-9aeb-ae7d0f236851_Humidity


    //  http://www.w3.org/ns/sosa/hasSimpleResult           **predicate for observedValue 
    //  objExple: “27.37”^^xsd:float

    

    char* object = NULL;

    if(strcmp(predicate, "http://www.w3.org/1999/02/22-rdf-syntax-ns#type") == 0)
    {
        object = getObjectSensorType(obs);
    }
    else if (strcmp(predicate, "http://www.w3.org/ns/sosa/observedProperty") == 0)
    {
        object = getObjectMoreSensorType(obs);
    }
    else if (strcmp(predicate, "http://www.w3.org/ns/sosa/phenomenonTime") == 0)
    {
        object = getObjectDateTime(obs);
    }
    else if (strcmp(predicate, "http://www.w3.org/ns/sosa/resultTime") == 0)
    {
        object = getObjectMoreDateTime(obs);
    }
    else if (strcmp(predicate, "http://www.w3.org/ns/sosa/madeBySensor") == 0)
    {
        object = getObjectOther(obs);
    }
    else if (strcmp(predicate, "http://www.w3.org/ns/sosa/hasSimpleResult") == 0)
    {
        object = getObjectObservedValue(obs);
    }

    return object;
}

char* getObjectSensorType(Observation* obs)
{
    //  objExple: https://coswot.gitlab.io/ontology#LuminosityObservation
    
    char init[50] = "https://coswot.gitlab.io/ontology";

    char sensorType1[30] = "LuminosityObservation";
    char sensorType2[30] = "TemperatureObservation";
    char sensorType3[30] = "HumidityObservation";

    char* elem = malloc(1 * sizeof(char));
    char* res = calloc(69,sizeof(char));

    elem[0] = '#';
    if( *(obs->sensorType) == 0 )
    {
        res = concatString(init,sensorType1,elem);
    }
    else if ( *(obs->sensorType) == 1 )
    {
        res = concatString(init,sensorType2,elem);
    }
    else if ( *(obs->sensorType) == 2 )
    {
        res = concatString(init,sensorType3,elem);
    }

    return res;
}

char* getObjectMoreSensorType(Observation* obs)
{
    // <http://example.org/id/property/emse_fauriel_4ET_405_sample1_ambientTemperatureProperty>;

    char init[50] = "http://example.org/id/property";
    
    char sensorType1[30] = "sample1_luminosityProperty";
    char sensorType2[50] = "sample1_ambientTemperatureProperty";
    char sensorType3[50] = "sample1_relativeHumidityProperty";

    char* elem = malloc(1 * sizeof(char));
    char* res = calloc(70,sizeof(char));
    char* buidingStairRoom = getAttr(obs);
    

    elem[0] = '/';
    res = concatString(init,buidingStairRoom,elem);

    elem[0] = '_';
    if( *(obs->sensorType) == 0 )
    {
        res = concatString(res,sensorType1,elem);
    }
    else if ( *(obs->sensorType) == 1 )
    {
        res = concatString(res,sensorType2,elem);
    }
    else if ( *(obs->sensorType) == 2 )
    {
        res = concatString(res,sensorType3,elem);
    }

    return res;
}

char* getObjectDateTime(Observation* obs)
{
    //  objExple: http://example.org/id/instant/2022-03-23T19:14:16

    char init[50] = "http://example.org/id/instant";
    char* elem = malloc(1 * sizeof(char));
    char* res = calloc(70,sizeof(char));
    char* dateTime = getTimesAttr(obs);

    elem[0] = '/';
    res = concatString(init,dateTime,elem);

    return res;
}

char* getObjectMoreDateTime(Observation* obs)
{
    //  objExple:  "2022-03-23T19:14:16Z"^^xsd:dateTime
    char* dateTime = getTimesAttr(obs);
    int lenRes = strlen(dateTime) + 1 +1;

    char* res = calloc(lenRes, sizeof(char));
    strcpy(res, dateTime);
    res[lenRes-2] = 'Z';

    return res;
}

char* getObjectOther(Observation* obs)
{
    //  objExple: http://example.org/id/sensor/emse_fauriel_4ET_405_6bd134b6-339c-4168-9aeb-ae7d0f236851_Humidity

    char init[50] = "http://example.org/id/sensor";
    
    char sensorType1[20] = "Luminosity";
    char sensorType2[20] = "Temperature";
    char sensorType3[20] = "Humidity";
    char outside[] = "outside";
    char* buidingStairRoom = getAttr(obs);

    char* elem = malloc(1 * sizeof(char));
    char* res = calloc(70,sizeof(char));
    

    elem[0] = '/';
    res = concatString(init,buidingStairRoom,elem);

    elem[0] = '_';
    if(obs->sensorID)
    {
        res = concatString(res,obs->sensorID,elem);
    }
    else
    {
        res = concatString(res,outside,elem);
    }

    elem[0] = '_';
    if( *(obs->sensorType) == 0 )
    {
        res = concatString(res,sensorType1,elem);
    }
    else if ( *(obs->sensorType) == 1 )
    {
        res = concatString(res,sensorType2,elem);
    }
    else if ( *(obs->sensorType) == 2 )
    {
        res = concatString(res,sensorType3,elem);
    }

    return res;
}

char* getTimesAttr(Observation* obs)
{
    // example: 2022-03-23T19:14:16

    char year[10];
    char month[10];
    char day[10];

    char hour[10];
    char minute[10];
    char second[10];

    char* elem = malloc(1 * sizeof(char));
    char* res = calloc(70,sizeof(char));


    elem[0] = '-';
    sprintf(year, "%d", obs->date.year); // To convert a int(obs->date.year) in a string(year)
    char* yearBis = dateTimeElemParse(year); //To be sure that the string passed contains more than one caracter

    sprintf(month, "%d", obs->date.month);
    char* monthBis = dateTimeElemParse(month);
    res = concatString(yearBis,monthBis,elem);
   
    elem[0] = '-';
    sprintf(day, "%d", obs->date.day);
    char* dayBis = dateTimeElemParse(day);
    res = concatString(res,dayBis,elem);
   
    elem[0] = 'T';
    sprintf(hour, "%d", obs->time.hour);
    char* hourBis = dateTimeElemParse(hour);
    res = concatString(res,hourBis,elem);

    elem[0] = ':';
    sprintf(minute, "%d", obs->time.minute);
    char* minuteBis = dateTimeElemParse(minute);
    res = concatString(res,minuteBis,elem);

    elem[0] = ':';
    sprintf(second, "%d", obs->time.second);
    char* secondBis = dateTimeElemParse(second);
    res = concatString(res,secondBis,elem);

    return res;
}

char* getAttr(Observation* obs)
{
    // example : emse_fauriel_4ET_405
    char* elem = malloc(1 * sizeof(char));
    char* res = calloc(70,sizeof(char));
    

    elem[0] = '_';
    res = concatString(obs->building, obs->stair, elem);

    elem[0] = '_';
    res = concatString(res,obs->room,elem);

    return res;
}

char* getObjectObservedValue(Observation* obs)
{
    //  objExple: “27.37”^^xsd:float   float is the datatype

    char observedValue[10];
    gcvt(obs->observedValue, 5, observedValue); //to convert a float to a string
    char* observedValueBis = dateTimeElemParse(observedValue); //To be sure that the string we will passed contains more than one caracter

    return observedValueBis;
}








    

    
