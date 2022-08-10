#include "Observation.h"
#define TAILLE_MAX 200


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
    }
    else
    {
        printf("Cannot open file");
    }
    return l;
}

Observation* readFromStream(char* stream)
{
    // 2022/03/23 19:14:16 emse/fayol/e4/S405/sensors/6bd134b6-339c-4168-9aeb-ae7d0f236851/metrics/LUMI 3
    // ------------------------------------------------OR--------------------------------------------------
    // 2022/03/23 19:15:20 emse/fayol/3ET/325/temperature/outside 13.36

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
            matObser[j] = malloc(strlen(token)* sizeof(char)) ; 
            strcpy(matObser[j],token );
       }
   }
   else
   {
       for(j=i+1; j<=i+5;j++)
       {
            token = strtok(NULL, "/");
            matObser[j] = malloc(strlen(token)* sizeof(char)) ; 
            strcpy(matObser[j],token );
       }
   } 
   
   token = strtok(NULL, " ");
   matObser[j] = malloc(strlen(token)* sizeof(char)) ; 
   strcpy(matObser[j],token );

   token = strtok(NULL, " ");
   matObser[j+1] = malloc(strlen(token)* sizeof(char)) ; 
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
   char* building = concatString(matObser[6], matObser[7]);

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
            //sensorType = Luminosity;
            (* sensorTypePointer) = Luminosity;
       }
       else if (strcmp(matObser[13], "TEMP") == 0)
       {
            //sensorType = Temperature;
            (* sensorTypePointer) = Temperature;
       }
       else if (strcmp(matObser[13], "HMDT") == 0)
       {
            //sensorType = Humidity;
            (* sensorTypePointer) = Humidity;
       }

   }
   
   // Attribute observedValue
   float observedValue;
   if(resp)
   {
       observedValue = atof(matObser[14]);
   }
   else
   {
       observedValue = atof(matObser[12]);
   } 
   

   // Construction of Observation
   Observation* observation  = malloc(sizeof(Observation)); //Instance

   (*observation).date = date;
   (*observation).time = time;
   (*observation).building = building;
   (*observation).stair = stair;
   (*observation).room = room;
   (*observation).sensorID = sensorID;
   if(resp)
   {
       (*observation).sensorType = sensorTypePointer;
   }
   else
   {
       (*observation).sensorType = NULL;
   }
   
   (*observation).observedValue = observedValue;


   return observation;

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
        

        if (SensorTypePointer)
        {
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
            
        }
        
        printf(" observedValue  : %f\n\n", (*obs).observedValue);
    }

}


char* concatString(char* str1, char* str2)
{
    int lenStr1 = strlen(str1);
    int lenStr2 = strlen(str2);
    int lenResult = lenStr1 + lenStr2+1;
    char* strResult = malloc(lenResult * sizeof(char));

    int i=0;
    while (i<lenStr1)
    {
        strResult[i] = str1[i];
        i++;
    }

    strResult[i] = '_'; i = i+1;

    int j=0;
    while (i<lenResult)
    {
        strResult[i] = str2[j];
        i++;
        j++;
    }
    return strResult;
}



