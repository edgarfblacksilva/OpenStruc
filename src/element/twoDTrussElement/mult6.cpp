#include "twoDTrussElement.h"

void TwoDTrussElement::mult6(real *__restrict const dg2fl ) 
{
    real *d=nullptr;
    dimVec(d,ThreeDFrameElement::dofPerElement);
    d[ 1] = dg2fl[1];
    d[ 2] = dg2fl[2];
    d[ 7] = dg2fl[3];
    d[ 8] = dg2fl[4];
    
    ThreeDFrameElement::mult6(d);
    
    dg2fl[1] = d[ 1];
    dg2fl[2] = d[ 2];
    dg2fl[3] = d[ 7];
    dg2fl[4] = d[ 8];
    
    freeVec(d);
} // end of TwoDTrussElement::mult6() //
