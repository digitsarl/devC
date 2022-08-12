#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Observation.h"


int main(int argc, char **argv)
{
    char* filepath = malloc(50*sizeof(char));
    filepath = "data/observations_externes.txt";

    // Storage of all observations in a LinkedList
    LinkedList* l = readFromFile(filepath);

    //Printing of all observations
    printObs(l);

    //Free the LinkedList
    freeLinkedList(l);

}

