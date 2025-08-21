#include "twoDTrussElement.h"

void TwoDTrussElement::getGlobalStiffnessMatrix(real **sm) 
{
    real **fullSm;
    dimMat(fullSm, ThreeDFrameElement::dofPerElement, ThreeDFrameElement::dofPerElement);
    ThreeDFrameElement::getGlobalStiffnessMatrix(fullSm);
    
    sm[1][1] = fullSm[1][1];
    sm[2][1] = fullSm[2][1];
    sm[3][1] = fullSm[7][1];
    sm[4][1] = fullSm[8][1];

    sm[2][2] = fullSm[2][2];
    sm[3][2] = fullSm[7][2];
    sm[4][2] = fullSm[8][2];

    sm[3][3] = fullSm[7][7];
    sm[4][3] = fullSm[8][7];
    
    sm[4][4] = fullSm[8][8];
                
    freeMat(fullSm);
} // end of TwoDTrussElement::getGlobalStiffnessMatrix() //

