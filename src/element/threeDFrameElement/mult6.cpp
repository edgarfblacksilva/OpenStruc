#include <iomanip>
using std::setw;
using std::setprecision;

#include <numeric>
using std::inner_product;

#include "threeDFrameElement.h"

void ThreeDFrameElement::mult6(real *__restrict const d)
{
   real *w=nullptr;
   dimVec(w, dofPerElement);

    for(auto l=zero; l < dofPerElement; l+=3) {
        for(auto k=zero, i=one; i<=3; ++i ) {
            for(auto j=one; j<=3; ++j) {
                w[l+i] += d[l+j]*r[k++];
            } // end for //
        } // end for //
    } // end for //

    real **a;
    dimMat(a,dofPerElement,dofPerElement);
    ThreeDFrameElement::getLocalStiffnessMatrix(a);
    
    for(auto i=one; i<=dofPerElement ; ++i) {
        d[i] = inner_product( &(a[i][1]),&(a[i][dofPerElement])+1,&w[1],0.0);
    } // endfor //

   freeMat(a);
   freeVec(w);
} // end of ThreeDFrameElement::mult6() //
