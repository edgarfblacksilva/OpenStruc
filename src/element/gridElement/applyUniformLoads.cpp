#include "gridElement.h"

#define square(x) ((x)*(x))

void GridElement::applyUniformLoads(real *__restrict const d, real &axiso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, const real &Wx, const real &Wy, const real &Wz, const real &a,const real &b) 
{
    auto ap = a + b;
    if (Wz != 0.0) {
        auto temp = Wz / (24 * square(length) * getIy());
        d[3] += temp * (square(length - a) * (square(length) + 2 * length * a - square(a))  -  square(length - ap) * (square(length) + 2 * length * ap - square(ap)));
        d[6] -= temp * (square(square(length) - square(a))  - square(square(length) - square(ap)) );
        vzisoi -= Wz/(2*length) * (square(length - a)  - square(length - ap));
        vzisoj += Wz * ( (square(length - a)/(2*length) - (length - a)) - (square(length - ap)/(2*length) - (length - ap)));
    } // end if //
    
    for(auto kk=dofPerElement, l=one; l<=secctionsInsideAnElement; ++l) {
        real xi = l * length / (secctionsInsideAnElement+1);
        real Vz {0.0}, amy{0.0};
        
        if (xi < a) {
            Vz = 0.0;
            amy = 0.0;
        } else if (xi >= a and xi <= ap) {
            Vz =  (xi - a) * Wz ;
            amy = (xi - a) * (xi - a) * (.5 * Wz );
        } else {
            Vz =  b * Wz ;
            amy = Vz * (xi - a -0.5*b) ;
        } // end if //
        
        forcesInElement[++kk] += Vz;
        kk+=2;
        forcesInElement[kk] += amy;
    } // end for l //
} // end of GridElement::applyUniformLoads() //
