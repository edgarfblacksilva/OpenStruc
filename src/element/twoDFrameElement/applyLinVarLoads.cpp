#include "twoDFrameElement.h"

void TwoDFrameElement::applyLinVarLoads(real *__restrict const d, real &axiso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, real Wxi, real Wxj, real Wyi, real Wyj, real Wzi, real Wzj, real a,const real &b)
{
    real atemp1 = Wxj;
    real atemp2 = Wyj;
    auto myloop=zero;
    if ((length - a - b) > 0) {
        Wxj = Wxi + (Wxj - Wxi) / b * (length - a);
        Wyj = Wyi + (Wyj - Wyi) / b * (length - a);
        myloop = 2;
    } else {
        myloop = 1;
    } // end if //
    real ra;
    
    for(auto loop=one; loop<=myloop; ++loop) {
    
        if (Wxi != 0.0 or Wxj != 0) {
            d[4]  -= (length - a) / ( getAr() * length) * (.5 * a * (Wxi + Wxj) + (length - a) * (Wxi + 2 * Wxj) / 6);
            axiso -=  0.5 * (Wxi + Wxj) * (length - a);
        } // end if //

        if (Wyi != 0.0 or Wyj != 0) {
            d[3] -=  (length - a) * (length - a) * (Wyi / (24 * length * length * getIz()) * (length * length + 2 * length * a - a * a) + (Wyj - Wyi) / (360 * length * length * getIz()) * (7 * length * length + 6 * a * length - 3 * a * a));
            d[6] += (Wyi / (24 * length * length * getIz()) * (length * length - a * a) * (length * length - a * a) + (Wyj - Wyi) / (360 * length * length * getIz()) * (length - a) * (length - a) * (8 * length * length + 9 * a * length + 3 * a * a));

            ra = (length - a) * (length - a) * (.5 * Wyi / length + (Wyj - Wyi) / (6 * length));
            vyisoi -=  ra;
            vyisoj +=  (ra - 0.5 * (length - a) * (Wyi + Wyj));
        } // end if //

        for(auto kk=dofPerElement, l=one; l<=secctionsInsideAnElement; ++l) {
            real xi = l * length / (secctionsInsideAnElement+1);
            real ax,Vy,amz;
            if (xi < a) {
                ax = 0.0;
                Vy = 0.0;
                amz = 0.0;
            } else {
                ax = -(xi - a) * (Wxi + .5 * (Wxj - Wxi) * (xi - a) / (length - a));
                Vy =  (xi - a) * (Wyi + .5 * (Wyj - Wyi) * (xi - a) / (length - a));
                amz = (xi - a) * (xi - a) * (.5 * Wyi + (Wyj - Wyi) * (xi - a) / (6 * (length - a)));
            } // end if //
            forcesInElement[++kk] += ax;
            forcesInElement[++kk] += Vy;
            forcesInElement[++kk] += amz;
        } // end for l //
        Wxj = -Wxj;
        Wyj = -Wyj;
        Wxi = -atemp1;
        Wyi = -atemp2;
        a += b;        
    } // end for loop //
} // end of TwoDFrameElement::applyLinVarLoads() //
