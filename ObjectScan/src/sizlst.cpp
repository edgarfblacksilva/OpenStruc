#include "ObjectScan.h"

int  Scan::sizlst(const int *list, const int &nl )
{
    int index=0;
    int ir=0;
    if (nl == 0) {
        return 0;
    } // end if //
    if (list[0] < 0) {
        return -1;
    } // end if //

    while (true) {
        ++index;
        ++ir;
        if (index >=nl) {
            break;
        } else if ( list[index] >=  0 ) {
            continue;
        } // end if //
        ir +=  ((abs(list[index])-list[index-1]+list[index+1])/list[index+1]) -2;
        ++index;
    } // end while //
    return(ir);
} // end of Scan::sizlst() //
