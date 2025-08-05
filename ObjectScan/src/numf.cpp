#include "ObjectScan.h"

bool Scan::numf(float &number)
{
    double dval;
    bool temp = false;
    if (numd(dval)) {
        number = static_cast<float>(dval);
        temp = true;
    } // end if //
    return temp;
} // end of Scan::numf() //
