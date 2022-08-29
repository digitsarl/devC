#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED


/**
 * concatenates two strings by inserting the content of the string "elemnt" in the middle.
 */
char* concatString(char* str1, char* str2, char* elemnt);

/**
 * parse the room attribute of and observation'instance. if it starts with the character 'S', this character is removed from the string representing the value of the attribute
 */
char* roomParse(char* initRoom);

/**
 * parse an element of date or time attribute.
 * Example: '3' is replace by "03"
 */
char* dateTimeElemParse(char* elem);


#endif // UTILS_H_INCLUDED
