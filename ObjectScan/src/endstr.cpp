#include "ObjectScan.h"

bool Scan::endstr()
{
    bool result;
    if (currentStringPos <= StringLength) {
        currentToken = (token[tokenIndex] + currentStringPos);
        size_t temp = strcspn(currentToken,separator);
        while (temp == 0) {
            ++currentStringPos;
            currentToken = (token[tokenIndex] + currentStringPos);
            temp = strcspn(currentToken,separator);
        } // end while //
        currentToken[temp]='\0';
        while (currentToken[++temp] == separator[0]) {
            // skiping separators
        } // end while //
        currentStringPos += temp;
        readyToMove=false;
        result = false;
    } else {
        StringLength = 0;
        doScan();
        result = true;
    } // end if //
    return result;
} // end of Scan::endstr()
