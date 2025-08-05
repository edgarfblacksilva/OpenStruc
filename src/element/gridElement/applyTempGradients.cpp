#include "gridElement.h"

void GridElement::applyTempGradients(real *__restrict const d,const real &ct,const real &ato1, const real &dty, const real &dtz, const real &by ,const real &bz)
{
    if (dtz != 0) {
        d[3] -= length * ct * dtz / (2 * bz);
        d[6] += length * ct * dtz / (2 * bz);
    } // end if //
} // end of GridElement::applyTempGradients() //
