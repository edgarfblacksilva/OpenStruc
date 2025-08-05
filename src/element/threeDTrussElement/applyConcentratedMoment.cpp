#include "threeDTrussElement.h"

void ThreeDTrussElement::applyConcentratedMoment(real *__restrict const d, real &pariso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, const real &Px, const real &Py, const real &Pz, const real &a) 
{
    if (Py != 0.0) {
        vzisoi -=  Py / length;
        vzisoj +=  Py / length;
    } // end if //

    if (Pz != 0.0) {
        vyisoi +=  Pz / length;
        vyisoj -=  Pz / length;
    } // end if //

} // end of ThreeDTrussElement::applyConcentratedMoment() //
