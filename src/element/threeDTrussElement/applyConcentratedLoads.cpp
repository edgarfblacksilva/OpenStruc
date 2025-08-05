#include "threeDTrussElement.h"

void ThreeDTrussElement::applyConcentratedLoads(real *__restrict const d, real &axiso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, const real &Px, const real &Py, const real &Pz, const real &a) 
{
    if (Px != 0.0) {
        d[4]  -=  Px * a / (getAr() * length);
        axiso -=  Px;
    } // end if //

    if (Py != 0.0) {
        vyisoi -=  Py * (length - a) / length;
        vyisoj -=  Py * a / length;
    } // end if //

    if (Pz != 0.0) {
        vzisoi -=  Pz * (length - a) / length;
        vzisoj -=  Pz * a / length;
    } // end if //

    for(auto kk=dofPerElement, l=one; l<=secctionsInsideAnElement; ++l) {
        real xi = l * length / (secctionsInsideAnElement+1);
        real ax {0.0},Vy {0.0} ,Vz {0.0};        
        if (xi >= a) {
            ax = -Px;
            Vy = Py;
            Vz = Pz;
        } // end if //
        forcesInElement[++kk] += ax;
        forcesInElement[++kk] += Vy;
        forcesInElement[++kk] += Vz;
    } // end for //
} // end of ThreeDTrussElement::applyConcentratedLoads() //
