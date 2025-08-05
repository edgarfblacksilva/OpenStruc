#include "openStruc.h"

void OpenStruc::getPrimaryForcesDueToGlobalTemp()
{
    auto elementForcesRecNber=zero;
    for(auto elementRecNber=zero; elementRecNber < numberOfElements; ++elementRecNber) {
        elm->read(elementRecNber);
        real temp = elm->getGlobalTempIncrement()*(elm->getAr()*elm->getLength()*ct[elm->getMatType()]);
        
        if (numberOfElementCombinations > 0) {
            elementForcesRecNber = numberOfLoadCases * elementRecNber + loadCase -1;
            //elementForcesRecNber = numberOfElementCombinations * elementRecNber + loadCase -1;
        } else {
            elementForcesRecNber=elementRecNber;
        } // end if //
        
        elm->readEF(elementForcesRecNber);
        elm->addForcesInElement( temp,                   1);
        elm->addForcesInElement(-temp,       1+dofPerJoint);
        elm->setForcesInElement(static_cast<real>(true), 0);  // Flag to indicate that there is primary forces in this member
        elm->writeEF(elementForcesRecNber);
    } // end for //
    areThereLoadedElements=true;
} // end of OpenStruc::setPrimaryForcesDueToGlobalTemp() //
