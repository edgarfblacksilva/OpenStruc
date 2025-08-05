#include "threeDFrameElement.h"

void ThreeDFrameElement::mult4(real *__restrict const w)
{
    mult4(w, forcesInElement);
} // end of ThreeDFrameElement::mult4() //

void ThreeDFrameElement::mult4(real *__restrict const w, const real *__restrict const d)
{
    for(auto l=zero; l < dofPerElement; l+=3) {
        for(auto i=one; i<=3; ++i ) {
            w[l+i] = 0.0;
            for(auto k=i-one,j=one; j<=3; ++j,k +=3) {
                w[l+i] += d[l+j]*r[k];
            } // end for //
        } // end for //
    } // end for //
} // end of ThreeDFrameElement::mult4() //
