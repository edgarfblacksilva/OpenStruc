#include<cmath>

#include "threeDFrameElement.h"

void ThreeDFrameElement::setElementLengthAndRotation(const  real *__restrict const ci, const real *__restrict const cj, real *pointP) 
{
    real cx,cy,cz;
    real xlp=0.0, ylp=0.0, zlp=0.0;
    //real shearAreaY,shearAreaZ;

    // setting element length//    
    cx = cj[0] - ci[0];
    cy = cj[1] - ci[1];
    cz = cj[2] - ci[2];
    
//    if (coordPerJoint==2) {
//        cz = 0.0;
//    } // end if //
    
    length=sqrt(cx*cx + cy*cy + cz*cz);

    // setting element rotation matrix in the r vector//    
    cx /= length;
    cy /= length;
    cz /= length;

    if (pointP != nullptr) {
        xlp = pointP[0] - ci[0];
        ylp = pointP[1] - ci[1];
        zlp = pointP[2] - ci[2];
    } // end if //

    real q = (cx * cx) + (cz * cz);
    if (q < .001) {  // Vertical members
        for(auto k=zero; k<9;++k){
            r[k] = 0.0;
        } // end for//
        r[1] = cy;
        if (pointP == nullptr) { // no Point P: Miembro vertical sin rotacion longitudinal
            r[3] = -cy;
            r[8] = 1.0;
        } else {                     //Miembro vertical con rotacion longitudinal
            real a = sqrt(xlp * xlp + zlp * zlp);
            real c = -xlp * cy / a;
            real ss = zlp / a;
            r[3] = -c * cy;
            r[5] = ss;
            r[6] = ss * cy;
            r[8] = c;
        } // end if //
    } else { // No vertical members
        q = sqrt(q);
        r[0] = cx;
        r[1] = cy;
        r[2] = cz;
        // Miembros no verticales sin rotacion longitudinal
        r[3] = -cx * cy / q;
        r[4] = q;
        r[5] = -cy * cz / q;
        r[6] = -cz / q;
        r[8] = cx / q;
        if (pointP == nullptr) { // no Point P:
            r[7] = 0;
        } else { // miembro no vertical con rotacion longitudinal
            real a = r[3] * xlp + r[4] * ylp + r[5] * zlp;
            real c = r[6] * xlp + r[8] * zlp;
            real d = sqrt(a * a + c * c);
            real ss = c / d;
            c = a / d;
            // cerr << " cos and sine of alpha : "<< c << "   " << ss << "\n";
            r[3] = (-cx * cy * c - cz * ss) / q;
            r[4] = q * c;
            r[5] = (-cz * cy * c + cx * ss) / q;
            r[6] = (cx * cy * ss - cz * c) / q;
            r[7] = -q * ss;
            r[8] = (cy * cz * ss + cx * c) / q;
        } // end if //
    } // end if //    
} // end of ThreeDFrameElement::setElementLengthAndRotation() //
