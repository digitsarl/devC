#include "Observation.h"

#ifndef FACTS_H_INCLUDED
#define FACTS_H_INCLUDED

/**
 * Add a quad (fact) to a model.
 */
bool AddFact(SordModel* mod, char* s, char* p, char* o, char* g);

/**
 * Add a quad (fact) to a model. But the object string will be converted to a sordNode literal
 */
void AddFactWithLiteralObject(SordModel* mod, char* s, char* p, char* o, char* g, SordNode* datatype);

/**
 * Add many quads (facts) to a model from an observation.
 */
bool AddFactsFromObservation(SordModel* mod, Observation* obs);


/**
 * Add many quads (facts) to a model from a LinkedList of observation.
 */
void AddFactsFromLinkedList(LinkedList* l, SordModel* mod);

/**
 * Add many quads (facts) to a model from a LinkedList of observation.
 */
void makeFileFacts(char* filepath, SordModel* mod);

/**
 * Return a string containing all facts of a model.
 */
char* printFact(SordModel* mod);

/**
 * Create a SordNode* uri instance from a str.
 */
SordNode* createSordNode(char* str, SordModel* mod);

/**
 * Create a SordNode* literal instance from a str.
 */
SordNode* createSordNodeLiteral(char* str, SordModel* mod);

/**
 * Create a SordNode* blank instance from a str.
 */
SordNode* createSordNodeBlank(char* str, SordModel* mod);


#endif // FACTS_H_INCLUDED