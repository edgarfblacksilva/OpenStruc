#include "threeDFrameElement.h"

void ThreeDFrameElement::applyConcentratedMoment(real *__restrict const d, real &pariso, real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, const real &Px, const real &Py, const real &Pz, const real &a) 
{
    if (Px != 0.0) {
        d[10]  -=  Px * a / (getIx() * length);
        pariso -=  Px;
    } // end if //

    if (Py != 0.0) {
        d[ 5] -=  Py / (6 * getIy() * length * length) * (2 * length * length - 6 * a * length + 3 * a * a);
        d[11] +=  Py / (6 * getIy() * length * length) * (length * length - 3 * a * a);
        vzisoi -=  Py / length;
        vzisoj +=  Py / length;
    } // end if //

    if (Pz != 0.0) {
        d[ 6] -=  Pz / (6 * getIz() * length * length) * (2 * length * length - 6 * a * length + 3 * a * a);
        d[12] +=  Pz / (6 * getIz() * length * length) * (length * length - 3 * a * a);
        vyisoi +=  Pz / length;
        vyisoj -=  Pz / length;
    } // end if //

    for(auto kk=one*16, l=one; l<=secctionsInsideAnElement; ++l) {
        real xi = l * length / (secctionsInsideAnElement+1);
        real par,amy,amz;
        if (xi < a) {
            par = 0.0;
            amy = 0.0;
            amz = 0.0;
        } else {
            par = -Px;
            amy = Py;
            amz = -Pz;
        } // end if //
        forcesInElement[kk] += par;
        forcesInElement[++kk] += amy;
        forcesInElement[++kk] += amz;
        kk +=4;
    } // end for l//
} // end of ThreeDFrameElement::applyConcentratedMoment() //
