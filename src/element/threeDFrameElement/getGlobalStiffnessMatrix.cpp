#include "threeDFrameElement.h"

void ThreeDFrameElement::getGlobalStiffnessMatrix(real **sm) 
{
  ThreeDFrameElement::getLocalStiffnessMatrix(sm);  

  real x;
  real **sa;
  dimMat(sa,dofPerElement,dofPerElement);
  
  for(auto l=zero; l<dofPerElement; l+=3){
     auto kkk=0;
     for(auto  kk=zero, lj=zero,j=one;j<=3;++j){
       kk = kkk++;
       lj=l+j;
       for(auto lk=zero, k=one;k<=3;++k){
          x = r[kk];
          kk+=3;
          if(x != 0){
            lk = l + k;
            for(auto i=one;i<=dofPerElement;++i){
               sa[i] [lj] += x * sm[i][ lk];
            } // end for //
          } //end if //
       } // end for //  
     } // end for //
  } // end for //


  for(auto l=zero; l<dofPerElement ; l+=3){
     auto kkk=zero;
     for(auto li=zero,i=one;i<=3;++i){
       auto kk = kkk++;
       li=l+i;
       for(auto j=one;j<=dofPerElement;++j){
         sm[li][j] = static_cast<real>(0.0);
       } // end for //
       for(auto lk=zero, k=one;k<=3;++k){
          x = r[kk];
          kk+=3;
          if(x != 0){
            lk = l + k;
            for(auto j=one;j<=dofPerElement;++j){
               sm[li] [j] += x * sa[lk][ j];
            } // end for //
          } //end if //
       } // end for //  
     } // end for //
  } // end for //
  
  freeMat(sa);      
} // end of ThreeDFrameElement::getGlobalStiffnessMatrix() //
