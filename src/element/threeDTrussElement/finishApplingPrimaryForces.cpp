#include <numeric>
using std::inner_product;

#include "threeDTrussElement.h"

void ThreeDTrussElement::finishApplingPrimaryForces(real *__restrict const d,const real &length,const real &axiso,const real &pariso,const real &vyisoi,const real &vyisoj,const real &vzisoi,const real &vzisoj)
{
    //  Creating the element stiffness matrix
    real **sm;
    real *dd=nullptr;
    dimMat(sm,ThreeDFrameElement::dofPerElement,ThreeDFrameElement::dofPerElement);
    dimVec(dd,ThreeDFrameElement::dofPerElement);
    //  end of Creating the element stiffness matrix
    
    dd[ 1] = d[1];
    dd[ 2] = d[2];
    dd[ 3] = d[3];
    dd[ 7] = d[4];
    dd[ 8] = d[5];
    dd[ 9] = d[6];
    
    ThreeDFrameElement::getLocalStiffnessMatrix(sm);
    
    forcesInElement[1] = inner_product( &(sm[1][1]),&(sm[1][12])+1, &dd[1], forcesInElement[1]);
    forcesInElement[2] = inner_product( &(sm[2][1]),&(sm[2][12])+1, &dd[1], forcesInElement[2]);
    forcesInElement[3] = inner_product( &(sm[3][1]),&(sm[3][12])+1, &dd[1], forcesInElement[3]);
    forcesInElement[4] = inner_product( &(sm[7][1]),&(sm[7][12])+1, &dd[1], forcesInElement[4]);
    forcesInElement[5] = inner_product( &(sm[8][1]),&(sm[8][12])+1, &dd[1], forcesInElement[5]);
    forcesInElement[6] = inner_product( &(sm[9][1]),&(sm[9][12])+1, &dd[1], forcesInElement[6]);

    freeMat(sm);
    freeVec(dd);

    forcesInElement[1] = axiso  - forcesInElement[4];
    forcesInElement[2] = vyisoi;
    forcesInElement[3] = vzisoi;
    forcesInElement[5] = vyisoj;
    forcesInElement[6] = vzisoj;
    
} // end of ThreeDTrussElement::finishApplingPrimaryForces() //
