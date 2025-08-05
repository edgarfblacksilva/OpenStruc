#include "threeDFrameElement.h"

void ThreeDFrameElement::applyTempGradients(real *__restrict const d,const real &ct, const real &ato1, const real &dty, const real &dtz, const real &by ,const real &bz)
{
    if (ato1 != 0) {
        d[7] -=  (ato1-globalTempIncrement) * length * ct;
    } // end if //

    if (dty != 0) {
        d[6]  += length * ct * dty / (2 * by);
        d[12] -= length * ct * dty / (2 * by);
    } // end if //

    if (dtz != 0) {
        d[5]  -= length * ct * dtz / (2 * bz);
        d[11] += length * ct * dtz / (2 * bz);
    } // end if //
} // end of ThreeDFrameElement::applyTempGradients() //

