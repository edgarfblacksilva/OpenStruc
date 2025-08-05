#include "gridElement.h"

void GridElement::mult4(real *__restrict const globalForces ) 
{
    real *w=nullptr;
    dimVec(w,ThreeDFrameElement::dofPerElement);
    
    real *d=nullptr;
    dimVec(d,ThreeDFrameElement::dofPerElement);
    
    d[ 3] = forcesInElement[1];
    d[ 4] = forcesInElement[2];
    d[ 5] = forcesInElement[3];
    d[ 9] = forcesInElement[4];
    d[10] = forcesInElement[5];
    d[11] = forcesInElement[6];
    
    ThreeDFrameElement::mult4(w, d);
    
    globalForces[1] = w[ 3];
    globalForces[2] = w[ 4];
    globalForces[3] = w[ 5];
    globalForces[4] = w[ 9];
    globalForces[5] = w[10];
    globalForces[6] = w[11];
    
    freeVec(d);
    freeVec(w);

} // end of GridElement::mult4() //
