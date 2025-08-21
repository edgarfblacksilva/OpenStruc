#include "ObjectScan.h"

void Scan::scan_contents(char *mytoken, positiveInt &nc)
{
    strcpy(mytoken,currentToken);
    nc = static_cast<positiveInt>(strlen(currentToken));
} // end of Scan::scan_contents() //
