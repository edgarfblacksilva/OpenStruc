#include "twoDTrussElement.h"

#define square(x) ((x)*(x))

void TwoDTrussElement::applyUniformLoads(real *__restrict const d, real &axiso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, const real &Wx, const real &Wy, const real &Wz, const real &a,const real &b) 
{
    auto ap = a + b;
    
    if (Wx != 0.0 ) {
        d[3]  -= Wx  / (2*getAr() * length) * ( (length+a) * (length-a)  - (length+ap) * (length-ap));
        axiso -= Wx * (ap - a);
    } // end if //
    
    if (Wy != 0.0 ) {
        vyisoi -= Wy/(2*length) * (square(length - a)  - square(length - ap));
        vyisoj += Wy * ( (square(length - a)/(2*length) - (length - a)) - (square(length - ap)/(2*length) - (length - ap)) );
    } // end if //
    
    for(auto kk=dofPerElement, l=one; l<=secctionsInsideAnElement; ++l) {
        real xi = l * length / (secctionsInsideAnElement+1);
        real ax {0.0},Vy{0.0};
        if (xi < a) {
            ax = 0.0;
            Vy = 0.0;
        } else if (xi >= a and xi <= ap) {
            ax = -(xi - a) * Wx ;
            Vy =  (xi - a) * Wy ;
        } else {
            ax = -b * Wx ;
            Vy =  b * Wy ;
        } // end if //
        
        forcesInElement[++kk] += ax;
        forcesInElement[++kk] += Vy;
    } // end for l //
} // end of TwoDTrussElement::applyUniformLoads() //
