#include "openStruc.h"

void OpenStruc::readIncidences()
{
    intPos jointI,jointJ, elementNber;
    int iVal;

    for (auto i=one; i<=numberOfElements; ++i) {
        do {
            readLine();        // this jumps empty lines        
        } while ( endcrd() );  //
        
        while (true) {
            if (integr(iVal)) {
                elementNber=static_cast<intPos>(iVal-1);
                if (integr(iVal)) {
                    jointI=static_cast<intPos>(iVal);
                } // end if //    
                if (integr(iVal)) {
                    jointJ=static_cast<intPos>(iVal);
                } // end if //
                //formLeftColumn(jointI,jointJ);  // Puse esta linea en printStrucData.cpp
                elm->setElementEndJoints(jointI,jointJ);
            } else if( endcrd() ) {
                break; // jump out of the while loop
            } // end if //  
        } // end while //
        elm->write(elementNber);
    } // end for //
} // end of OpenStruc::readIncidences() //
