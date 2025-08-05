#include "ObjectScan.h"

bool Scan::matchs(const char *str, const positiveInt &nchar  )
{
    if (readyToMove) {
        doScan();
    } // end if //

    if (currentToken == nullptr) {
       return false;
    } // end if //
    
    char *tempStr1;
    char *tempStr2;
    bool result;

    tempStr1 = new char[nchar];
    tempStr2 = new char[nchar];
    tempStr1 = toLowerStr(strncpy(tempStr1,str,         nchar),nchar);
    tempStr2 = toLowerStr(strncpy(tempStr2,currentToken,nchar),nchar);

    if (!endcrd() and strncmp(tempStr1,tempStr2,nchar) == 0) {
        readyToMove=true;
        result = true;
    } else {
        result = false;
    } // end if //
    delete [] tempStr1;
    delete [] tempStr2;
    return result;    
} // end of Scan::matchs() //
