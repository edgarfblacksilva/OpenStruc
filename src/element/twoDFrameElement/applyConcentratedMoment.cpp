#include "twoDFrameElement.h"

void TwoDFrameElement::applyConcentratedMoment(real *__restrict const d, real &pariso, real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, const real &Px, const real &Py, const real &Pz, const real &a) 
{
    if (Pz != 0.0) {
        d[3] -=  Pz / (6 * getIz() * length * length) * (2 * length * length - 6 * a * length + 3 * a * a);
        d[6] +=  Pz / (6 * getIz() * length * length) * (length * length - 3 * a * a);
        vyisoi +=  Pz / length;
        vyisoj -=  Pz / length;
    } // end if //

    for(auto kk=one*9, l=one; l<=secctionsInsideAnElement; ++l) {
        real xi = l * length / (secctionsInsideAnElement+1);
        real amz;
        if (xi < a) {
            amz = 0.0;
        } else {
            amz = -Pz;
        } // end if //
        forcesInElement[kk] += amz;
        kk +=3;
    } // end for l//
} // end of TwoDFrameElement::applyConcentratedMoment() //

