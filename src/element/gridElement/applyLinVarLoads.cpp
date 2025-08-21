#include "gridElement.h"

void GridElement::applyLinVarLoads(real *__restrict const d, real &axiso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, real Wxi, real Wxj, real Wyi, real Wyj, real Wzi, real Wzj, real a,const real &b)
{
    real atemp3 = Wzj;
    auto myloop=zero;
    
    if ((length - a - b) > 0) {
        //Wxj = Wxi + (Wxj - Wxi) / b * (length - a);
        //Wyj = Wyi + (Wyj - Wyi) / b * (length - a);
        Wzj = Wzi + (Wzj - Wzi) / b * (length - a);
        myloop = 2;
    } else {
        myloop = 1;
    } // end if //
    
    for(auto loop=one; loop<=myloop; ++loop) {
        if (Wzi != 0.0 or Wzj != 0) {
            d[3] +=  (length - a) * (length - a) * (Wzi / (24 * length * length * getIy()) * (length * length + 2 * length * a - a * a) + (Wzj - Wzi) / (360 * length * length * getIy()) * (7 * length * length + 6 * a * length - 3 * a * a));
            d[6] -= (Wzi / (24 * length * length * getIy()) * (length * length - a * a) * (length * length - a * a) + (Wzj - Wzi) / (360 * length * length * getIy()) * (length - a) * (length - a) * (8 * length * length + 9 * a * length + 3 * a * a));

            auto ra = (length - a) * (length - a) * (.5 * Wzi / length + (Wzj - Wzi) / (6 * length));
            vzisoi -=  ra;
            vzisoj +=  (ra - .5 * (length - a) * (Wzi + Wzj));
        } // end if //
    
        for(auto kk=dofPerElement, l=one; l<=secctionsInsideAnElement; ++l) {
            real xi = l * length / (secctionsInsideAnElement+1);
            real Vz{0.0},amy{0.0};
            if (xi < a) {
                Vz = 0.0;
                amy = 0.0;
            } else {
                Vz =  (xi - a) * (Wzi + .5 * (Wzj - Wzi) * (xi - a) / (length - a));
                amy = (xi - a) * (xi - a) * (.5 * Wzi + (Wzj - Wzi) * (xi - a) / (6 * (length - a)));
            } // end if //
            forcesInElement[++kk] += Vz;
            kk+=2;
            forcesInElement[kk] += amy;
        } // end for l //
        Wzj = -Wzj;
        Wzi = -atemp3;
        a += b;        
    } // end for loop //
} // end of GridElement::applyLinVarLoads() //
