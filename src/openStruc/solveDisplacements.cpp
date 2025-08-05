#include "openStruc.h"

void OpenStruc::solveDisplacements() {

    string message[2];

#if defined (ENGLISH)
    message[0] = "Solving system using LDL\n";
    message[1] = "Solving system using Cholesky\n";
#elif defined (ESPANOL)
    message[0] = "Resolviendo el sistema usando LDL\n";
    message[1] = "Resolviendo el sistema usando Cholesky\n";  
#endif    


    //    impose boundary conditions on global load Vector

    auto jointRecNber=zero;
    auto countingConstraints=zero;
    do  {
        jnt->read(jointRecNber);
        if (jnt->getTypeOfRestriction() > 0 ) {
            ++countingConstraints;
            auto row = (jointRecNber)*dofPerJoint + 1;
            for(auto k=zero; k < dofPerJoint; ++k,++row) {
                if (constraint[jointRecNber][k] ) {
                    loadVector[row]= 0.0;
                } // end if //
            } // end for //
        } // end if //
        ++jointRecNber;
    } while (countingConstraints < numberOfSuppNodes); // end do //
    
#if defined (LDL)
    cerr << message[0];
    ldl   (cout,structureStiffnessMatrix,loadVector, numberOfEqations,leftCol);
#elif defined (CHOLESKY)
    cerr << message[1];
    choles(cout,structureStiffnessMatrix,loadVector, numberOfEqations,leftCol);
#endif
} // end of OpenStruc::solveDisplacements() //
