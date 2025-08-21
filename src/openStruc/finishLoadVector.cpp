#include "openStruc.h"

void OpenStruc::finishLoadVector()
{
    bool logico=false;
    auto elementForcesRecNber=zero;
    for(auto elementRecNber=zero; elementRecNber < numberOfElements; ++elementRecNber) {
        if (numberOfElementCombinations > 0) {            
            elementForcesRecNber = numberOfLoadCases * elementRecNber + loadCase -1; // see finishLoadVector in newAd1
        } else {
            elementForcesRecNber=elementRecNber;
        } // end if //
        elm->readEF(elementForcesRecNber);

        real *globalForces=nullptr;
        dimVec(globalForces,dofPerElement);
        if (  static_cast<bool>(elm->getForcesInElement(0))  ) {
            elm->read(elementRecNber);
            elm->mult4(globalForces);
            
            auto k=(elm->getElementJointI()-1)*dofPerJoint + 1;
            
            for(auto ii=one; ii<=dofPerJoint; ++ii, ++k) {
                loadVector[k] -= globalForces[ii];
            } // end for //
            k=(elm->getElementJointJ()-1)*dofPerJoint + 1;
            //cerr <<"  kj: " << k << '\n';
            for(auto ii=one+dofPerJoint; ii<=dofPerElement; ++ii, ++k) {
                loadVector[k] -= globalForces[ii];
            } // end for //
            
            if (lineNumber > 53) {
                header();
                cout << titleCase[loadCase] << "\n\n";
                lineNumber+=2;
                elm->printElementInfo(2);lineNumber+=2;
                logico = true;
            } // end if //
            if (logico == false) {
                elm->printElementInfo(2);lineNumber+=2;
                logico = true;
            } // end if //
            elm->printElementPrimaryForces(elementRecNber, lineNumber);
        } // end if //
        freeVec(globalForces);
    } // end for //
    cout << '\n';
    ++lineNumber;     
} // end of OpenStruc::finishLoadVector(() //
