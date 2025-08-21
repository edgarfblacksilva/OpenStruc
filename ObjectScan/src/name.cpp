#include "ObjectScan.h"

bool Scan::name()
{
    if (readyToMove) {
        doScan();
    } // end if //
    if (!endcrd() and isalpha(currentToken[0])  and strchr(currentToken, '.') != NULL) {
        positiveInt i,j=1,n;
        n=strlen(currentToken);
        for (i=1;i<n ;++i ) {
            if (currentToken[i] == '.') {
                currentToken[j++] = currentToken[i+1];
            } // end if //
            currentToken[j]='\0';
        } // end for //
        readyToMove=true;
    } else {
        readyToMove=false;
    } // end if //
    return readyToMove;
} // end of Scan::name() //
