#include "ObjectScan.h"

bool Scan::floatn(float &number)
{
    bool result = false;
    int itemp;
    if (integr(itemp)) {
        readyToMove=false;
    } else {
        double dval;
        if (numd(dval)) {
            number = static_cast<float>(dval);
            result = true;
        } // end if //
    } // end if //
    return result;
} // end of Scan::floatn() //
