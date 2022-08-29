#include "Observation.h"
#include "Facts.h"

int main(int argc, char **argv)
{
    //Create a SordWorld object
    SordWorld* world = sord_world_new();

    //Create a SordModel object
    SordModel* kb = sord_new(world, SORD_SPO, true);

    //Create the filepath to read the differents stream of observations
    char* filepathRead = (char*)malloc(50*sizeof(char));
    strcpy(filepathRead, "data/observations.txt" );

    //Create the filepath to write the differents facts extracts from a model (sordModel)
    char* filepathWrite = (char*)malloc(50*sizeof(char));
    strcpy(filepathWrite, "data/facts.ttl" );

    // Storage of all observations in a LinkedList
    LinkedList* l = readFromFile(filepathRead);

    //Add many quads (facts) to a model from a LinkedList of observation.
    AddFactsFromLinkedList(l,kb);

    //write the facts to a file
    makeFileFacts(filepathWrite, kb);

    // get the string of facts
    char* out = printFact(kb);

    //Printing of all observations
    //printObs(l);

    //print the string of facts
    /*printf("\n\n*************************print of differents facts :******************************\n\n");
    printf("%s\n", out);*/

    //small test
    char initialFactFilePath[20] = "data/facts.ttl";
    printf("small test to verify if the facts are well copy in the facts.ttl file\n");
    test(initialFactFilePath);

    //free the filepath to read the differents stream of observations
    free(filepathRead);

    //free the filepath to write the differents facts
    free(filepathWrite);
    
    //Free the string of facts
    free(out);

    //Free the LinkedList
    //freeLinkedList(l);

    //Free the model
    sord_free(kb);

    //Free the world
    sord_world_free(world);

    

    /*char* subject = getSubject(l->first->data);
    printf("Le sujet est : %s\n", subject);*/

   

    /*char* obj1 = getObjectSensorType(l->first->data);
    printf("L'object sensortype est : %s\n", obj1);

    char* obj2 = getObjectDateTime(l->first->data);
    printf("L'object date et time est : %s\n", obj2);

    char* obj3 = getObjectOther(l->first->data);
    printf("L'object des autres est : %s\n", obj3);

    char* obj4 = getObjectObservedValue(l->first->data);
    printf("L'object observedValue est : %s\n", obj4);
    
    char* obj5 = getObjectMoreSensorType(l->first->data);
    printf("Plus d'info sur sensortype : %s\n", obj5);
    
    char* obj6 = getTimesAttr(l->first->data);
    printf("Plus d'info sur sensortype : %s\n", obj6);*/


    /*AddFactsFromObservation(kb,l->first->data);
    printf("%zu facts we have add.\n", sord_num_quads(kb));

    AddFactsFromObservation(kb,l->first->next->data);*/
    char* obj7 = getObjectMoreDateTime(l->first->data);
    printf("Plus d'info sur date et time : %s\n", obj7);

    
    

    
    


    
    
    return 0;
}

