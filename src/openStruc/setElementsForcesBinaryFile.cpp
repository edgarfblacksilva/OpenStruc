#include "openStruc.h"

void OpenStruc::setElementsForcesBinaryFile()
{
    elm->clearForcesInElement();
    auto elementForcesRecNber=zero;
    
    for(auto elementRecNber=zero; elementRecNber<numberOfElements; ++elementRecNber) {
        if (numberOfElementCombinations > 0) {
            elementForcesRecNber = numberOfLoadCases * elementRecNber + loadCase -1;
        } else {
            elementForcesRecNber=elementRecNber;
        } // end if //    
        elm->writeEF(elementForcesRecNber);        
    } // end for //    
} // end of OpenStruc::setElementsForcesBinaryFile() //
