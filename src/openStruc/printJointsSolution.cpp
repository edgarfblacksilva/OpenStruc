#include "openStruc.h"

void OpenStruc::printJointsSolution() 
{
    auto jointReactionRecNber = loadCase-1;
    for(auto jointRecNber=zero, k=one; jointRecNber<numberOfNodes; ++jointRecNber) {
        jnt->read(jointRecNber);
        
        for(auto i=zero; i<dofPerJoint; ++i, ++k) {
            loadVector[k] += jnt->getLoadReac(i);
            jnt->setJointReactionsRecord(loadVector[k],i);
            jnt->setLoadReac(0.0,i);
        } // end for //
        jnt->write(jointRecNber);
        jnt->writeReac(jointReactionRecNber);
        jointReactionRecNber+=numberOfLoadCases;
    } // end for //
    
    if (lineNumber > 53) {
        header();
        cout << titleCase[loadCase] << "\n\n";
        lineNumber+=2;
    } // end if //
    jnt->printJointInfo(4);lineNumber+=2;


    for(auto i=one, k = one; i<=numberOfNodes; ++i ) {
        if (lineNumber > 56) {
            header();
            cout << titleCase[loadCase] << "\n\n";
            lineNumber+=2;
            jnt->printJointInfo(4);lineNumber+=2;
        } // end if //
        
        cout << setw(8) << i << setprecision(4);
        for(auto j=one; j<=dofPerJoint; ++j, ++k) {
            cout << setw(12) << loadVector[k];
        } // end for //
        cout << '\n';
        ++lineNumber;
    } // end for //
} // end of OpenStruc::printJointsSolution() //
