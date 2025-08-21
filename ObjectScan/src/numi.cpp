#include "ObjectScan.h"

bool Scan::numi(int &number)
{
    bool result = false;
    
    if (integr(number)) {    
        result = true;
    } else {
        double dval;
        if (numd(dval)) {
            number = static_cast<int>(dval);
            result = true;
        } // end if //
    } // end if //
    return result;
} // end of Scan::numi() //
