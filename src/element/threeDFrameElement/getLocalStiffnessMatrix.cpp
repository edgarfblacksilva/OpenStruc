#include "threeDFrameElement.h"

void ThreeDFrameElement::getLocalStiffnessMatrix(real **sm) 
{
    real &ael  = properties[0];
    real &gkl  = properties[1];
    real &eiyl = properties[2];
    real &eizl = properties[3];


    real &ciy = stiffnessFactors[0];
    real &cjy = stiffnessFactors[1];
    real &cy  = stiffnessFactors[2];
    real &c   = stiffnessFactors[3];
    real &ciz = stiffnessFactors[4];
    real &cjz = stiffnessFactors[5];
    real &cz  = stiffnessFactors[6];

    real ct1, ct2,ct3;
    real eiyl2, eiyl3, eizl2, eizl3;
    
    for (auto i=one; i<=dofPerElement ; ++i) {
       for (auto j=one; j<=i ; ++j) {
          sm[i][j] = static_cast<real>(0.0);
        } // end for //
     } // end for //

    eiyl2 = eiyl  / length;
    eiyl3 = eiyl2 / length;
    eizl2 = eizl  / length;
    eizl3 = eizl2 / length;

    sm[1][ 1]   =  ael * c;
    sm[7][ 1]   = -ael * c; 
    sm[7][ 7]   =  ael * c; 
    sm[4][ 4]   =  gkl * c;
    sm[10][4]   = -gkl * c;
    sm[10][ 10] =  gkl * c;

    ct1 = ciz + cz;
    ct2 = cjz + cz;
    ct3 = ct1 + ct2;
    
    sm[2][ 2] =  eizl3 * ct3;
    sm[6][ 2] =  eizl2 * ct1;
    sm[8][ 2] = -eizl3 * ct3;
    sm[12][ 2] = eizl2 * ct2;
    
    sm[6][ 6]   =   eizl  * ciz;
    sm[8][ 6]   =  -eizl2 * ct1;
    sm[12][6]   =   eizl  * cz;
    sm[8][ 8]   =   eizl3 * ct3;
    sm[12][8]   =  -eizl2 * ct2;
    sm[12][ 12] =   eizl  * cjz;

    ct1 = ciy + cy;
    ct2 = cjy + cy;
    ct3 = ct1 + ct2;

    sm[3][3]  =   eiyl3 * ct3;
    sm[5][3]  =  -eiyl2 * ct1;
    sm[9][3]  =  -eiyl3 * ct3;
    sm[11][3] =  -eiyl2 * ct2;

    sm[5][5]   = eiyl * ciy;    
    sm[9][5]   = eiyl2 * ct1;
    sm[11][5]  = eiyl * cy;    
    sm[9][9]   = eiyl3 * ct3;
    sm[11][9]  = eiyl2 * ct2;
    sm[11][11] = eiyl * cjy;

    
    for (auto i=one; i<=dofPerElement; ++i) {
      for (auto j=one+1; j<=dofPerElement; ++j) {
        sm[i][j]= sm[j][i];
      } // end for //
    } // end for //  
  
} // end of ThreeDFrameElement::getLocalStiffnessMatrix() //
