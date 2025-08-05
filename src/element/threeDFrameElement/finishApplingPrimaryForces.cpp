#include <numeric>
using std::inner_product;

#include "threeDFrameElement.h"

void ThreeDFrameElement::finishApplingPrimaryForces(real *__restrict const d,const real &length,const real &axiso,const real &pariso,const real &vyisoi,const real &vyisoj,const real &vzisoi,const real &vzisoj)
{
    //  Creating the element stiffness matrix
    real **sm;
    dimMat(sm,ThreeDFrameElement::dofPerElement,ThreeDFrameElement::dofPerElement);
    //  end of Creating the element stiffness matrix
    
    this->getLocalStiffnessMatrix(sm);
    for(auto i=one; i<=12 ; ++i) {
        forcesInElement[i] = inner_product( &(sm[i][1]),&(sm[i][12])+1, &d[1], forcesInElement[i]);
    } // endfor //
    freeMat(sm);

    forcesInElement[1] = axiso  - forcesInElement[7];
    forcesInElement[2] = vyisoi + (forcesInElement[6] + forcesInElement[12]) / length;
    forcesInElement[3] = vzisoi - (forcesInElement[5] + forcesInElement[11]) / length;
    forcesInElement[4] = pariso - forcesInElement[10];
    forcesInElement[8] = vyisoj - (forcesInElement[6] + forcesInElement[12]) / length;
    forcesInElement[9] = vzisoj + (forcesInElement[5] + forcesInElement[11]) / length;
} // end of ThreeDFrameElement::finishApplingPrimaryForces() //

