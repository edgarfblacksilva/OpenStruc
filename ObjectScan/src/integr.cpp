#include "ObjectScan.h"

bool Scan::integr(int &number)
{
    if (readyToMove) {
        doScan();
    } // end if //
    
    if (!endcrd()) {
        positiveInt i=0;
        positiveInt length = strlen(currentToken);
        if ( currentToken[0] == '+' or currentToken[0] == '-' ) {
            ++i;
        } // end if //
        do {
            if (isdigit(currentToken[i])) {
                ++i;
            } else {
                readyToMove=false;
                return false;
            } // end if //
        } while (i < length); // end do While//
        number = atoi(currentToken);
        readyToMove=true;
        return true;
    } // end if //
    return false;
} // end of Scan::integr(() //
