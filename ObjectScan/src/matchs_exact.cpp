#include "ObjectScan.h"

bool Scan::matchs_exact(const char *str)
{
    if (readyToMove) {
        doScan();
    } // end if //
    
    bool result = false;
    if (!endcrd() and tokenPerLine > 0) {
        positiveInt nchar=strlen(token[tokenIndex]);
        if( matchs(str, nchar) and nchar == strlen(str)) {
            result = true;
        } // end if //
    } else {
        readyToMove=false;
    } // end if //
    return result;
} // end of Scan::matchs_exact()
