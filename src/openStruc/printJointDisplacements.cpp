#include "openStruc.h"

void OpenStruc::printJointDisplacements() 
{
    // From now on loadVector has the global displacements
    if (lineNumber + numberOfNodes + 2 > 56) {
        header();
        cout << titleCase[loadCase] << "\n\n";
        lineNumber+=2;        
    } // end if //
    
    jnt->printJointInfo(3);lineNumber+=2;
    cout << scientific;
    
    for(auto jointRecNber=zero, row=one; jointRecNber < numberOfNodes; ++jointRecNber) {
        jnt->read(jointRecNber);
        cout << setw( 8) << jointRecNber+1 << setprecision(6);
        for(auto j=zero; j<dofPerJoint; ++j,++row) {
            if (lineNumber > 56) {
                header();
                cout << titleCase[loadCase] << "\n\n";
                lineNumber+=2;
                jnt->printJointInfo(3);lineNumber+=2;
            } // end if //        
            cout << setw(16) << scientific  << (loadVector[row] + jnt->getInitialDisp(j) );
            //jnt->setInitialDisp(0.0, j);
        }// end for //
        jnt->cleanInitialDisp();
        jnt->write(jointRecNber);
        cout << '\n'; ++lineNumber;
    } // end for //
    cout << '\n'; ++lineNumber;
    
    if ((elm->getSecctionsInsideAnElement() == 0 and lineNumber > 54) or (elm->getSecctionsInsideAnElement() > 0 and lineNumber > 51) ) {
        header();
        cout << titleCase[loadCase] << "\n\n";
        lineNumber+=2;
    } // end if //
} // end of OpenStruc::printJointDisplacements() //
