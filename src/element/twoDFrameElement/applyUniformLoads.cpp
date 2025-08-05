#include "twoDFrameElement.h"

#define square(x) ((x)*(x))

void TwoDFrameElement::applyUniformLoads(real *__restrict const d, real &axiso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, const real &Wx, const real &Wy, const real &Wz, const  real &a,const real &b) 
{
    auto ap = a + b;
    
    if (Wx != 0.0 ) {
        d[4]  -= Wx  / (2*getAr() * length) * ( (length+a) * (length-a)  - (length+ap) * (length-ap));
        axiso -= Wx * (ap - a);
    } // end if //
    
    if (Wy != 0.0 ) {
        auto temp = Wy / (24 * square(length) * getIz());
        d[3] -= temp * ( square(length - a) * (square(length) + 2*a*length - square(a)) - square(length - ap) * (square(length) + 2*ap*length - square(ap)) );
        d[6] += temp * (square(square(length) - square(a)) - square(square(length) - square(ap)));
        vyisoi -= Wy/(2*length) * (square(length - a)  - square(length - ap));
        vyisoj += Wy * ( (square(length - a)/(2*length) - (length - a)) - (square(length - ap)/(2*length) - (length - ap)) );
    } // end if //
    
    
    for(auto kk=dofPerElement, l=one; l<=secctionsInsideAnElement; ++l) {
        real xi = l * length / (secctionsInsideAnElement+1);
        real ax,Vy,amz; //,Vz,amy
        if (xi < a) {
            ax = 0.0;
            Vy = 0.0;
            amz = 0.0;
        } else if (xi >= a and xi <= ap) {
            ax = -(xi - a) * Wx ;
            Vy =  (xi - a) * Wy ;
            amz = (xi - a) * (xi - a) * (.5 * Wy );
        } else {
            ax = -b * Wx ;
            Vy =  b * Wy ;
            amz = Vy * (xi - a -0.5*b);
        } // end if //
        
        forcesInElement[++kk] += ax;
        forcesInElement[++kk] += Vy;
        forcesInElement[++kk] += amz;
    } // end for l //
} // end of TwoDFrameElement::applyUniformLoads() //
