#include "ObjectScan.h"

bool Scan::label()
{
    if (readyToMove) {
        doScan();
    } // end if //
    
    if (!endcrd()  and (isalpha(currentToken[0]) or currentToken[0] == '_' ) and strchr(currentToken, '.') == nullptr ) {
        readyToMove = true;
    } else {
        readyToMove = false;
    } // end if //
    return readyToMove;
} // end of Scan::label() //
