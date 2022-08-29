#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

/**
 * concatenates two strings by putting "_" in the middle.
 */
char* concatString(char* str1, char* str2, char* elemnt);

/**
 * parse the room attribute.
 */
char* roomParse(char* initRoom);

/**
 * parse an element of date or time attribute.
 */
char* dateTimeElemParse(char* elem);


#endif // UTILS_H_INCLUDED
