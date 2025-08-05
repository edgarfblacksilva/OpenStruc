#include "gridElement.h"

void GridElement::getGlobalStiffnessMatrix(real **sm) {
    // sm is a clean 6X6 lowerTriangularRagedMatrix
    real **fullSm;
    dimMat(fullSm, ThreeDFrameElement::dofPerElement, ThreeDFrameElement::dofPerElement);
    
    ThreeDFrameElement::getGlobalStiffnessMatrix(fullSm);

    sm[1][1] = fullSm[3][3];
    sm[2][1] = fullSm[4][3];
    sm[3][1] = fullSm[5][3];
    sm[4][1] = fullSm[9][3];
    sm[5][1] = fullSm[10][3];
    sm[6][1] = fullSm[11][3];


    sm[2][2] = fullSm[4][4];
    sm[3][2] = fullSm[5][4];
    sm[4][2] = fullSm[9][4];
    sm[5][2] = fullSm[10][4];
    sm[6][2] = fullSm[11][4];

    sm[3][3] = fullSm[5][5];
    sm[4][3] = fullSm[9][5];
    sm[5][3] = fullSm[10][5];
    sm[6][3] = fullSm[11][5];

    sm[4][4] = fullSm[9][9];
    sm[5][4] = fullSm[10][9];
    sm[6][4] = fullSm[11][9];

    sm[5][5] = fullSm[10][10];
    sm[6][5] = fullSm[11][10];

    sm[6][6] = fullSm[11][11];

    freeMat(fullSm);
} // end of GridElement::getGlobalStiffnessMatrix() //

