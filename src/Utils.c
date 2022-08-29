#include "Utils.h"

// ----------------------------------- Utils -------------------------------------

char* concatString(char* str1, char* str2, char* elemnt)
{
    int lenStr1 = strlen(str1);
    int lenStr2 = strlen(str2);
    int lenResult = lenStr1 + lenStr2 + 1 + 1;
    char* strResult = calloc(lenResult,sizeof(char));
    
    int i=0;
    while (i<lenStr1)
    {
        strResult[i] = str1[i];
        i++;
    }

    strResult[i] = elemnt[0]; i = i+1;

    int j=0;
    while (i<lenResult)
    {
        strResult[i] = str2[j];
        i++;
        j++;
    }
    
    return strResult;
}

char* roomParse(char* initRoom)
{
    if(initRoom[0] == 'S')
    {
        int lenResult  = strlen(initRoom);
        char* finalRoom = malloc(lenResult * sizeof(char));

        int i = 1;
        while (i<=lenResult)
        {
            finalRoom[i-1] = initRoom[i];
            i++;
        }

        return finalRoom;
    }
    return initRoom;
}


char* dateTimeElemParse(char* elem)
{
    int len =  strlen(elem);
    if(len == 1)
    {
        char* res = calloc(3,sizeof(char));
        res[0] = '0';
        res[1] = elem[0];

        return res;
    }
    else
    {
        char* resOther = calloc( (len+1), sizeof(char));
        strcpy(resOther,elem);
        return resOther;
    }
}