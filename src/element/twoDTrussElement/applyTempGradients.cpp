#include "twoDTrussElement.h"

void TwoDTrussElement::applyTempGradients(real *__restrict const d,const real &ct,const real &ato1, const real &dty, const real &dtz, const real &by ,const real &bz)
{
    if (ato1 != 0) {
        d[3] -=  (ato1-globalTempIncrement) * length * ct;
    } // end if //

} // end of TwoDTrussElement::applyTempGradients() //
