#include "gridElement.h"

void GridElement::applyUniformTorsion(real *__restrict const d, real &pariso, const real &Tx, const real &a,const real &b) 
{
    if (Tx != 0.0) {
        d[5]  -=  Tx / ( getIx() * length) * (a * b + .5 * b * b);
        pariso -=  Tx * b;
    } // end if //

    for(auto kk=one*8, l=one; l<=secctionsInsideAnElement; ++l) {
        real xi = l * length / (secctionsInsideAnElement+1);
        real par {0.0};
        if(xi >= a and xi <= (a + b)) {
            par = -(xi - a) * Tx;
        } else if(xi > (a + b)) {
            par = -Tx * b;
        } // end if //
        forcesInElement[kk] += par;
        kk += 3;
    } // end for l//
} // end of GridElement::applyUniformTorsion() //
