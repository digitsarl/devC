#include "Observation.h"

#ifndef FACTS_H_INCLUDED
#define FACTS_H_INCLUDED


/**
 * Add a quad (fact) to a model.
 */
void AddFact(SordModel* mod, char* s, char* p, char* o, char* g);

/**
 * Add a quad (fact) to a model. But the object string will be converted to a sordNode literal
 * @param datatype is a string that will be converted to a SordNode URI representing the datatype associated to the SordNode literal.
 */
void AddFactWithLiteralObject(SordModel* mod, char* s, char* p, char* o, char* g, char* datatype);

/**
 * Add many quads (facts) to a model from an observation's instance.
 */
void AddFactsFromObservation(SordModel* mod, Observation* obs);

/**
 * Add many quads (facts) to a model from a LinkedList of observation'instances.
 */
void AddFactsFromLinkedList(LinkedList* l, SordModel* mod);

/**
 * Write many quads (facts) in the file. these facts are extracted from a model.
 */
void makeFileFacts(char* filepath, SordModel* mod);

/**
 * Display in console the facts contained in a model .
 */
void printFact(SordModel* mod);

/**
 * Create a SordNode* uri instance from a str.
 */
SordNode* createSordNode(char* str, SordModel* mod);

/**
 * Create a SordNode* literal instance from a str.
 */
SordNode* createSordNodeLiteral(char* str, SordModel* mod);

/**
 * reads and counts the number of facts contained in a file.
 */
void readFileOfFacts(char* initialFactFilePath);


#endif // FACTS_H_INCLUDED