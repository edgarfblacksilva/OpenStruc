#include "gridElement.h"

void GridElement::mult6(real *__restrict const dg2fl ) 
{
    real *d=nullptr;
    dimVec(d,ThreeDFrameElement::dofPerElement);
    d[ 3] = dg2fl[1];
    d[ 4] = dg2fl[2];
    d[ 5] = dg2fl[3];
    d[ 9] = dg2fl[4];
    d[10] = dg2fl[5];
    d[11] = dg2fl[6];
    
    ThreeDFrameElement::mult6(d);
    
    dg2fl[1] = d[ 3];
    dg2fl[2] = d[ 4];
    dg2fl[3] = d[ 5];
    dg2fl[4] = d[ 9];
    dg2fl[5] = d[10];
    dg2fl[6] = d[11];
    
    freeVec(d);
} // end of GridElement::mult6() //
