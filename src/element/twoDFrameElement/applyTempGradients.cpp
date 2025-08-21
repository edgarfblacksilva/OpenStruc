#include "twoDFrameElement.h"

void TwoDFrameElement::applyTempGradients(real *__restrict const d,const real &ct,const real &ato1, const real &dty, const real &dtz, const real &by ,const real &bz)
{
    if (ato1 != 0) {
        d[4] -=  (ato1-globalTempIncrement) * length * ct;
    } // end if //

    if (dty != 0) {
        d[3] += length * ct * dty / (2 * by);
        d[6] -= length * ct * dty / (2 * by);
    } // end if //
    
} // end of TwoDFrameElement::applyTempGradients() //
