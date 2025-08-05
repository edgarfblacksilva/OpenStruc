#include "ObjectScan.h"

bool Scan::isstring()
{
    if (readyToMove) {
        doScan();
    } // end if //

    if (!endcrd()  and (currentToken[0] == '"' or currentToken[0] == '\'')) {
        currentToken = (token[tokenIndex] + 1);
        StringLength = strlen(currentToken);
        if (StringLength > 0) {
            --StringLength;
            if (currentToken[StringLength] == '"' or currentToken[StringLength] == '\'') {
                currentToken[StringLength] = '\0';
            } // end if //
        } // end if //
        readyToMove = true;
    } else {
        readyToMove = false;
    } // end if //
    return readyToMove;
} // end of Scan::isstring() //
