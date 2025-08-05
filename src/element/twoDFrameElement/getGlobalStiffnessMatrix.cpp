#include "twoDFrameElement.h"

void TwoDFrameElement::getGlobalStiffnessMatrix(real **sm) 
{
    real **fullSm;
    dimMat(fullSm, ThreeDFrameElement::dofPerElement, ThreeDFrameElement::dofPerElement);
    
    ThreeDFrameElement::getGlobalStiffnessMatrix(fullSm);
    
    sm[1][1] = fullSm[1][1];
    sm[2][1] = fullSm[2][1];
    sm[3][1] = fullSm[6][1];
    sm[4][1] = fullSm[7][1];
    sm[5][1] = fullSm[8][1];
    sm[6][1] = fullSm[12][1];

    sm[2][2] = fullSm[2][2];
    sm[3][2] = fullSm[6][2];
    sm[4][2] = fullSm[7][2];
    sm[5][2] = fullSm[8][2];
    sm[6][2] = fullSm[12][2];

    sm[3][3] = fullSm[6][6];
    sm[4][3] = fullSm[7][6];
    sm[5][3] = fullSm[8][6];
    sm[6][3] = fullSm[12][6];
    
    sm[4][4] = fullSm[7][7];
    sm[5][4] = fullSm[8][7];
    sm[6][4] = fullSm[12][7];
    
    sm[5][5] = fullSm[8][8];
    sm[6][5] = fullSm[12][8];
    
    sm[6][6] = fullSm[12][12];
                
    freeMat(fullSm);
} // end of TwoDFrameElement::getGlobalStiffnessMatrix() //
