#include "ObjectScan.h"

void Scan::backsp(const positiveInt &nument)
{
    if (tokenIndex > nument) {
        tokenIndex -= nument;
    } else {
        tokenIndex = 0;
        readyToMove=false;
    } // end if //
    currentToken = token[tokenIndex];
} // end of Scan::backsp() //
