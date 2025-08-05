#include "openStruc.h"

void OpenStruc::assembleGlobalStifnessMatrix() {
    //  Local Variables
    real **elementStiffnessMatrix;
    intPos *destinationVector=nullptr;
    //  End of local variables

    //  Creating the global stiffness ragged matrix
    dimMatVarBandW(structureStiffnessMatrix,numberOfEqations,leftCol);
    dimMat(elementStiffnessMatrix,dofPerElement,dofPerElement);
    dimVec(destinationVector,dofPerElement);
    //  end of Creating the global stiffness ragged matrix

    for(auto elementNber=one; elementNber<=numberOfElements; ++elementNber) {
        elm->read(elementNber-1);

        elm->getGlobalStiffnessMatrix(elementStiffnessMatrix);

        // creating the destination Vector
        auto ji = (elm->getElementJointI()-1)*dofPerJoint;
        auto jj = (elm->getElementJointJ()-1)*dofPerJoint;
        for (auto i=one; i<=dofPerJoint; ++i){
            destinationVector[i] = ++ji;
            if (constraint[elm->getElementJointI()-1][i-1] == true) {
                destinationVector[i] = 0;      
            } // end if //

            destinationVector[i + dofPerJoint] = ++jj;      
            if (constraint[elm->getElementJointJ()-1][i-1] == true) {
                destinationVector[i+ dofPerJoint] = 0;      
            } // end if     
        } // end for //

        // assembling and imposing boundary conditions on global stffness matrix
        for (auto i=one; i<=dofPerElement; ++i) {
            auto row = destinationVector[i];
            if (row > 0) {
                for (auto j=one; j<=i; ++j) {
                    auto col = destinationVector[j];
                    if (col > 0) {
                        if (row >= col) {
                            structureStiffnessMatrix[row][col] += elementStiffnessMatrix[i][j];
                        } else {
                            structureStiffnessMatrix[col][row] += elementStiffnessMatrix[i][j];
                        } // end if //
                    } // end if //
                } // end for //
            } // end if //
        } // end for //
    } // end for //

    // modifing the stffness matrix due to elastic supports

    real *springsConstants=nullptr;
    dimVec(springsConstants,dofPerJoint);
    for (auto jointNber=one; jointNber<=numberOfNodes; ++jointNber) {
        jnt->read(jointNber-1);    

        if (jnt->getTypeOfRestriction() == 2) {
            jnt->getSpringConstants(&springsConstants[1]);
            auto row = (jointNber-1)*dofPerJoint + 1;
            for (auto k=one; k <= dofPerJoint; ++k, ++row) {
                structureStiffnessMatrix[row][row] += springsConstants[k];
            } // end for //    
        } // end if //      
    } // end for //
    freeVec(springsConstants);

    for (auto row=one; row<=numberOfEqations; ++row) {
        if (structureStiffnessMatrix[row][row] == 0) {
            structureStiffnessMatrix[row][row] = 1.0;
        } // end if //
    } // end for //
    
    /*  I belive that the following code is not necesary. It was substituded by the loop above.
        for (auto row=one; row<=numberOfEqations; ++row) {
        if (structureStiffnessMatrix[row][row] == 0) {
        auto col = leftCol[row];
        while ((col<row) and (structureStiffnessMatrix[row][col] == 0.0)) {
        ++ col;
        } // end for //
        if (row == col) { // The whole row is empty
        structureStiffnessMatrix[row][col] = 1.0;
        } else { 
        cerr << "Error in row: " << row << " of the structure stifness matrix. Quitting....\n" ;
        cout << "Error in row: " << row << " of the structure stifness matrix. Quitting....\n" ;
        exit(0);
        } // end if //
        } // end if //
        } // end for //

     */  

    // call subroutine ldl or cholesky to solve the system
    // of algebraic equation the solution is returned in the array glf

    string message[2];
    //message = new string[2];  

#if defined (ENGLISH)
    message[0] = "Reducing matrix using LDL\n";
    message[1] = "Reducing matrix using Cholesky\n";
#elif defined (ESPANOL)
    message[0] = "Reduciendo la mariz usando LDL\n";
    message[1] = "Reduciendo la mariz usando Cholesky\n";  
#endif    


#if defined (LDL)
    cerr << message[0];
    ldl   (cout,structureStiffnessMatrix,    numberOfEqations,leftCol);     // Factorization of matrix stiff
#elif defined (CHOLESKY)
    cerr << message[1];
    choles(cout,structureStiffnessMatrix,    numberOfEqations,leftCol);  // Factorization of matrix stiff
#endif

    freeMat(elementStiffnessMatrix);
    freeVec(destinationVector);    
} // end of OpenStruc::assembleGlobalStifnessMatrix() //
