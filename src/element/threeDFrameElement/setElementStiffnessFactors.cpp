#include "threeDFrameElement.h"

void ThreeDFrameElement::setElementStiffnessFactors(const real &fyy, const real &fzz, real z1,real z2,const bool &shearDeformation,  const bool &releasesI, const bool &releasesJ) 
{
    real fy; // = fyy / (length*length);
    real fz; // = fzz / (length*length);
    
    if (!shearDeformation) {
        fy = 0;
        fz = 0;
    } else {
        fy = fyy / (length*length);
        fz = fzz / (length*length);
    } // end if //
    
    
    z1 /= length;
    z2 /= length;
    real z3 = 1 - z1 - z2;

    real c1 = z3 * (3 * z1 * z3 + 3 * z1 * z1 + z3 * z3) / 3;
    real c2 = z3 * (3 * z2 * z3 + 3 * z2 * z2 + z3 * z3) / 3;
    real c3 = z3 * (6 * z2 * z1 + 3 * z3 - 2 * z3 * z3)  / 6;

    stiffnessFactors[0] = c1 + fy * z3;
    stiffnessFactors[1] = c2 + fy * z3;
    stiffnessFactors[2] = c3 - fy * z3;
    stiffnessFactors[3] = stiffnessFactors[0] * stiffnessFactors[1] - stiffnessFactors[2]*stiffnessFactors[2];

    stiffnessFactors[0] /=  stiffnessFactors[3];
    stiffnessFactors[1] /=  stiffnessFactors[3];
    stiffnessFactors[2] /=  stiffnessFactors[3];

    stiffnessFactors[4] = c1 + fz * z3;
    stiffnessFactors[5] = c2 + fz * z3;
    stiffnessFactors[6] = c3 - fz * z3;

    stiffnessFactors[3] = stiffnessFactors[4] * stiffnessFactors[5] - stiffnessFactors[6]*stiffnessFactors[6];

    stiffnessFactors[4] /=  stiffnessFactors[3];
    stiffnessFactors[5] /=  stiffnessFactors[3];
    stiffnessFactors[6] /=  stiffnessFactors[3];

    stiffnessFactors[3] = 1 / z3;

    if (releasesI==true and releasesJ==false) {
        stiffnessFactors[5] -= (stiffnessFactors[6]*stiffnessFactors[6])/ stiffnessFactors[4];
        stiffnessFactors[4] = 0;
        stiffnessFactors[6] = 0;
        stiffnessFactors[1] -= (stiffnessFactors[2]*stiffnessFactors[2]) / stiffnessFactors[0];
        stiffnessFactors[0] = 0;
        stiffnessFactors[2] = 0;
    } else if (releasesI==false and releasesJ==true) {
        stiffnessFactors[4] -=  (stiffnessFactors[6]*stiffnessFactors[6]) / stiffnessFactors[5];
        stiffnessFactors[5] = 0;
        stiffnessFactors[6] = 0;
        stiffnessFactors[0] -= (stiffnessFactors[2]*stiffnessFactors[2])  / stiffnessFactors[1];
        stiffnessFactors[1] = 0;
        stiffnessFactors[2] = 0;
    } else if (releasesI==true and releasesJ==true) {
        stiffnessFactors[0] = 0;
        stiffnessFactors[1] = 0;
        stiffnessFactors[2] = 0;
        stiffnessFactors[4] = 0;
        stiffnessFactors[5] = 0;
        stiffnessFactors[6] = 0;
        //elementRecord.ax = 0.0; 
    } // end if //
} // end of ThreeDFrameElement::setElementStiffnessFactors() //
