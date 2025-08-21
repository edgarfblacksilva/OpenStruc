#include "gridElement.h"

void GridElement::applyConcentratedLoads(real *__restrict const d, real &axiso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, const real &Px, const real &Py, const real &Pz, const real &a) 
{
    if (Pz != 0.0) {
        d[3] +=  Pz * a * (length - a) * (2 * length - a) / (6 * length * length * getIy() );
        d[6] -= Pz * a * (length * length - a * a) / (6 * length * length * getIy() );
        vzisoi -=  Pz * (length - a) / length;
        vzisoj -=  Pz * a / length;
    } // end if //

    for(auto kk=dofPerElement, l=one; l<=secctionsInsideAnElement; ++l) {
        real xi = l * length / (secctionsInsideAnElement+1);
        real Vz{0.0}, amy={0.0};
        
        if (xi >= a) {
            Vz = Pz;
            amy = Pz * (xi - a);
        } // end if //
        forcesInElement[++kk] += Vz;
        kk+=2;
        forcesInElement[kk] += amy;
    } // end for //
} // end of GridElement::applyConcentratedLoads() //
