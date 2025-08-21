#include "openStruc.h"

void OpenStruc::readMaterials()
{
    double val;
    for (auto i=one; i<=numberOfMaterials; ++i) {    
        readLine();            // this force the material data to be in their own line
        while ( endcrd() ) {
            readLine();        // this jumps empty lines
        } // end while //
        while (true) {
            if (matchs("e", 1) ) {
                if (numd(val)) {
                   e[i] = static_cast<real>(val);
                } // end if //
            } else if(matchs("g", 1)) {
                if (numd(val)) {
                   g[i] = static_cast<real>(val);
                } // end if //
            } else if(matchs("ct", 2)) {
                if (numd(val)) {
                   ct[i] = static_cast<real>(val);
                } // end if //
            } else if(matchs("weight", 4)) {
                if (numd(val)) {
                   weight[i] = static_cast<real>(val);
                } // end if //        
            } else if( endcrd() ) {
                break; // jump out of the while loop
            } // end if //
        } // end while //        
    } // end for //    
} // end of OpenStruc::readMaterials() //
