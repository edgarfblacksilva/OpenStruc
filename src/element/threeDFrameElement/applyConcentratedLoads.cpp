#include "threeDFrameElement.h"

void ThreeDFrameElement::applyConcentratedLoads(real *__restrict const d, real &axiso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, const real &Px, const real &Py, const real &Pz, const real &a) 
{
    if (Px != 0.0) {
        d[7]  -=  Px * a / (getAr() * length);
        axiso -=  Px;
    } // end if //

    if (Py != 0.0) {
        d[ 6] -= Py * a * (length - a) * (2 * length - a) / (6 * length * length * getIz() );
        d[12] +=  Py * a * (length * length - a * a) / (6 * length * length * getIz());
        vyisoi -=  Py * (length - a) / length;
        vyisoj -=  Py * a / length;
    } // end if //

    if (Pz != 0.0) {
        d[5] +=  Pz * a * (length - a) * (2 * length - a) / (6 * length * length * getIy() );
        d[11] -= Pz * a * (length * length - a * a) / (6 * length * length * getIy() );
        vzisoi -=  Pz * (length - a) / length;
        vzisoj -=  Pz * a / length;
    } // end if //

    for(auto kk=dofPerElement, l=one; l<=secctionsInsideAnElement; ++l) {
        real xi = l * length / (secctionsInsideAnElement+1);
        real ax {0.0},Vy{0.0},Vz{0.0},amy{0.0},amz{0.0};
        if (xi >= a) {
            ax = -Px;
            Vy = Py;
            Vz = Pz;
            amy = Pz * (xi - a);
            amz = Py * (xi - a);
        } // end if //
        forcesInElement[++kk] += ax;
        forcesInElement[++kk] += Vy;
        forcesInElement[++kk] += Vz;
        ++kk;
        forcesInElement[++kk] += amy;
        forcesInElement[++kk] += amz;
    } // end for //
} // end of ThreeDFrameElement::applyConcentratedLoads() //
