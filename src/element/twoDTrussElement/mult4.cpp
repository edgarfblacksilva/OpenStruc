#include "twoDTrussElement.h"

void TwoDTrussElement::mult4(real *__restrict const globalForces ) 
{
    real *w=nullptr;
    dimVec(w,ThreeDFrameElement::dofPerElement);
    
    real *d=nullptr;
    dimVec(d,ThreeDFrameElement::dofPerElement);
    
    d[ 1] = forcesInElement[1];
    d[ 2] = forcesInElement[2];
    d[ 7] = forcesInElement[3];
    d[ 8] = forcesInElement[4];

    ThreeDFrameElement::mult4(w, d);
    
    globalForces[1] = w[1];
    globalForces[2] = w[2];
    globalForces[3] = w[7];
    globalForces[4] = w[8];
    
    freeVec(d);
    freeVec(w);
} // end of TwoDTrussElement::mult4() //
