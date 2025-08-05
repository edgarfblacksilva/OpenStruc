#include "gridElement.h"

void GridElement::applyConcentratedMoment(real *__restrict const d, real &pariso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, const real &Px, const real &Py, const real &Pz, const real &a) 
{
    if (Px != 0.0) {
        d[5]   -=  Px * a / (getIx() * length);
        pariso -=  Px;
    } // end if //

    if (Py != 0.0) {
        d[3] -=  Py / (6 * getIy() * length * length) * (2 * length * length - 6 * a * length + 3 * a * a);
        d[6] +=  Py / (6 * getIy() * length * length) * (length * length - 3 * a * a);
        vzisoi -=  Py / length;
        vzisoj +=  Py / length;
    } // end if //

    for(auto kk=one*8, l=one; l<=secctionsInsideAnElement; ++l) {
        real xi = l * length / (secctionsInsideAnElement+1);
        real par{0.0}, amy{0.0};
        if (xi < a) {
            par = 0.0;
            amy = 0.0;
        } else {
            par = -Px;
            amy = Py;
        } // end if //
        forcesInElement[kk] += par;
        forcesInElement[++kk] += amy;
        kk +=2;
    } // end for l//
} // end of GridElement::applyConcentratedMoment() //
