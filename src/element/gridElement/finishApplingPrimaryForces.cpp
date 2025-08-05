#include <numeric>
using std::inner_product;
#include "gridElement.h"


void GridElement::finishApplingPrimaryForces(real *__restrict const d,const real &length,const real &axiso,const real &pariso,const real &vyisoi,const real &vyisoj,const real &vzisoi,const real &vzisoj)
{
    //  Creating the element stiffness matrix
    real **sm;
    real *dd=nullptr;
    dimMat(sm,ThreeDFrameElement::dofPerElement,ThreeDFrameElement::dofPerElement);
    dimVec(dd,ThreeDFrameElement::dofPerElement);
    
    //  end of Creating the element stiffness matrix
    dd[ 3] = d[1];
    dd[ 4] = d[2];
    dd[ 5] = d[3];
    dd[ 9] = d[4];
    dd[10] = d[5];
    dd[11] = d[6];
    
    ThreeDFrameElement::getLocalStiffnessMatrix(sm);    

    forcesInElement[1] = inner_product( &(sm[ 3][1]),&(sm[3][12])+1,  &dd[1], forcesInElement[1]);
    forcesInElement[2] = inner_product( &(sm[ 4][1]),&(sm[4][12])+1,  &dd[1], forcesInElement[2]);
    forcesInElement[3] = inner_product( &(sm[ 5][1]),&(sm[5][12])+1,  &dd[1], forcesInElement[3]);
    forcesInElement[4] = inner_product( &(sm[ 9][1]),&(sm[9][12])+1,  &dd[1], forcesInElement[4]);
    forcesInElement[5] = inner_product( &(sm[10][1]),&(sm[10][12])+1, &dd[1], forcesInElement[5]);
    forcesInElement[6] = inner_product( &(sm[11][1]),&(sm[11][12])+1, &dd[1], forcesInElement[6]);

    freeMat(sm);
    freeVec(dd);
    
    forcesInElement[1] = vzisoi - (forcesInElement[3] + forcesInElement[6]) / length;
    forcesInElement[2] = pariso - forcesInElement[5];
    forcesInElement[4] = vzisoj + (forcesInElement[3] + forcesInElement[6]) / length;    
} // end of GridElement::finishApplingPrimaryForces() //
