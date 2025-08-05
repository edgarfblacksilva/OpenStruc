#include "ObjectScan.h"

char * Scan::toLowerStr(char *myString, const positiveInt &nchar)
{
    for (positiveInt i=0; i < nchar ;++i) {
        myString[i] = tolower(myString[i]);
    } // end for //
    return myString;
} // end of Scan::toLowerStr() 
