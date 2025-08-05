#include "threeDTrussElement.h"

void ThreeDTrussElement::applyTempGradients(real *__restrict const d,const real &ct,const real &ato1, const real &dty, const real &dtz, const real &by ,const real &bz)
{
    if (ato1 != 0) {
        d[4] -=  (ato1-globalTempIncrement) * length * ct;
    } // end if //
} // end of ThreeDTrussElement::applyTempGradients() //
