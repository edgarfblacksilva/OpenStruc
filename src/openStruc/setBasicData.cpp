#include "openStruc.h"

void OpenStruc::setBasicData()
{
    int iVal=0;
    matchs_exact("of");

    while (true) {
        if (matchs_exact("nodes")) {
            if (integr(iVal)) {
                setNumberOfNodes(static_cast<intPos>(iVal) );                
                numberOfEqations = numberOfNodes*dofPerJoint;
                dimMat(constraint,0,numberOfNodes-1,0,dofPerJoint-1);
                dimVec(loadVector,numberOfEqations);
                dimVec(leftCol,numberOfEqations);
                for (auto i=one; i<=numberOfEqations ;++i) { // initializing left column //
                    leftCol[i] = i;
                } // endfor //
            } else {
                cerr << errorMessage[0] << errorMessage[1] << getLineCounter() << '\n'; exit(0); 
            } // endif //
        } else if (matchs("elements", 6) ) {
            if (integr(iVal)) {
                setNumberOfElements(static_cast<intPos>(iVal));
            } else {
                cerr << errorMessage[0] << errorMessage[2] << getLineCounter() << '\n'; exit(0); 
            } // endif //
        } else if (matchs("materials", 4) ) {
            if (integr(iVal)) {
                setNumberOfMaterials(static_cast<intPos>(iVal));
                dimVec(e,     numberOfMaterials);
                dimVec(g,     numberOfMaterials);
                dimVec(ct,    numberOfMaterials);
                dimVec(weight,numberOfMaterials);
            } else {
                cerr << errorMessage[0] << errorMessage[1] << getLineCounter() << '\n'; exit(0); 
            } // endif //                
        } else if (matchs("load_Cases", 7) ) {
            if (integr(iVal)) {        
                setNumberOfLoadCases(static_cast<intPos>(iVal));
                dimVec(titleCase,numberOfLoadCases);
                //printStrucData();
                //assembleGlobalStifnessMatrix();    // mostly ade1c.cpp 
            } else {
                cerr << errorMessage[0] << errorMessage[2]<< getLineCounter() << '\n'; exit(0); 
            } // endif //

        } else if (matchs("elem_combinations", 9) ) {
            if (integr(iVal)) {
                setNumberOfElementCombinations(static_cast<intPos>(iVal));
            } else {
                cerr << errorMessage[12]  << getLineCounter() << '\n'; exit(0); 
            } // end if //
        } else if (matchs("node_combinations", 9) ) {
            if (integr(iVal)) {
                setNumberOfNodeCombinations(static_cast<intPos>(iVal));
            } else {
                cerr << errorMessage[12]  << getLineCounter() << '\n'; exit(0); 
            } // end if //
            
        } else if (matchs("section_Types", 10) ) {
            if (numberOfMaterials > 0) {
                if (integr(iVal)) {        
                    setNumberOfSectionTypes(static_cast<intPos>(iVal));
                } else {
                    cerr << errorMessage[0] << errorMessage[2] << getLineCounter() << '\n'; exit(0); 
                } // endif //            
            } else {            
                cerr << errorMessage[3]; exit(0);
            } // end if //
        } else if ( endcrd() ) {
            break;
        } else  {
            doScan();
            continue;
        } // endif //
    } // end while //
} // end of OpenStruc::setBasicData() //
