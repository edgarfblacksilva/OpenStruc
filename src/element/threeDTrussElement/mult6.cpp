#include "threeDTrussElement.h"

void ThreeDTrussElement::mult6(real *__restrict const dg2fl ) 
{
    real *d=nullptr;
    dimVec(d,ThreeDFrameElement::dofPerElement);
    d[ 1] = dg2fl[1];
    d[ 2] = dg2fl[2];
    d[ 3] = dg2fl[3];
    d[ 7] = dg2fl[4];
    d[ 8] = dg2fl[5];
    d[ 9] = dg2fl[6];
    
    ThreeDFrameElement::mult6(d);
    
    dg2fl[1] = d[ 1];
    dg2fl[2] = d[ 2];
    dg2fl[3] = d[ 3];
    dg2fl[4] = d[ 7];
    dg2fl[5] = d[ 8];
    dg2fl[6] = d[ 9];
    
    freeVec(d);
} // end of ThreeDTrussElement::mult6() //
