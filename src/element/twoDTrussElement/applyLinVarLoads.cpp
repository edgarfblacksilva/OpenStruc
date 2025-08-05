#include "twoDTrussElement.h"

void TwoDTrussElement::applyLinVarLoads(real *__restrict const d, real &axiso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, real Wxi, real Wxj, real Wyi, real Wyj, real Wzi, real Wzj, real a,const real &b)
{
    real atemp1 = Wxj;
    real atemp2 = Wyj;
    //real atemp3 = Wzj;
    auto myloop=zero;
    if ((length - a - b) > 0) {
        Wxj = Wxi + (Wxj - Wxi) / b * (length - a);
        Wyj = Wyi + (Wyj - Wyi) / b * (length - a);
        //Wzj = Wzi + (Wzj - Wzi) / b * (length - a);
        myloop = 2;
    } else {
        myloop = 1;
    } // end if //
    
    for(auto loop=one; loop<=myloop; ++loop) {
    
        if (Wxi != 0.0 or Wxj != 0) {
            d[3]  -= (length - a) / ( getAr() * length) * (.5 * a * (Wxi + Wxj) + (length - a) * (Wxi + 2 * Wxj) / 6);
            axiso -=  0.5 * (Wxi + Wxj) * (length - a);
        } // end if //


        if (Wyi != 0.0 or Wyj != 0) {
            auto ra = (length - a) * (length - a) * (.5 * Wyi / length + (Wyj - Wyi) / (6 * length));
            vyisoi -=  ra;
            vyisoj +=  (ra - 0.5 * (length - a) * (Wyi + Wyj));
        } // end if //

    
        for(auto kk=one*12, l=one; l<=secctionsInsideAnElement; ++l) {
            real xi = l * length / (secctionsInsideAnElement+1);
            real ax {0.0} ,Vy {0.0};
            if (xi < a) {
                ax = 0.0;
                Vy = 0.0;
            } else {
                ax = -(xi - a) * (Wxi + .5 * (Wxj - Wxi) * (xi - a) / (length - a));
                Vy =  (xi - a) * (Wyi + .5 * (Wyj - Wyi) * (xi - a) / (length - a));
            } // end if //
            forcesInElement[++kk] += ax;
            forcesInElement[++kk] += Vy;
        } // end for l //
        Wxj = -Wxj;
        Wyj = -Wyj;
        
        Wxi = -atemp1;
        Wyi = -atemp2;
        a += b;        
    } // end for loop //
} // end of TwoDTrussElement::applyLinVarLoads() //
