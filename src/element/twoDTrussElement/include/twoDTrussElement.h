#ifndef TWODTRUSSELEMENT
#define TWODTRUSSELEMENT

#include "threeDFrameElement.h"

class TwoDTrussElement: public ThreeDFrameElement 
{
    public:
        TwoDTrussElement(const string &filename, intPos &DofPerElement, const intPos &siae = 0);
        ~TwoDTrussElement() {;} // end of TwoDTrussElement destructor //
        
        virtual void getGlobalStiffnessMatrix(real **);
        
    private:    
        inline real getAr(){return properties[0];}
        virtual void mult4(real *__restrict const globalForces);
        virtual void mult6(real *__restrict const dg2fl);
        
        static constexpr intPos dofPerElement {4};
        virtual void printElementPrimaryForces(const intPos &, intPos &);
        virtual void applyLinVarLoads(real *__restrict const d, real &axiso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, real Wxi, real Wxj, real Wyi, real Wyj, real Wzi, real Wzj, real a,const real &b);
        virtual void applyUniformTorsion(real *__restrict const d, real &pariso, const real &Tx, const real &a, const real &b){/* empty function */ ;}
        virtual void applyConcentratedMoment(real *__restrict const d, real &pariso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, const real &cx,const real &cy,const real &cz, const real &a);        
        virtual void applyConcentratedLoads(real *__restrict const d, real &axiso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, const real &cx, const real &cy, const real &cz,const  real &a);
        virtual void applyUniformLoads(real *__restrict const d, real &axiso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, const real &Wx, const real &Wy,const real &Wz, const real &a,const real &b);
        virtual void applyTempGradients(real *__restrict const d,const real &ct,const real &ato1, const real &dty, const real &dtz, const real &by ,const real &bz);
        virtual void finishApplingPrimaryForces(real *__restrict const d,const real &length,const real &axiso,const real &pariso,const real &vyisoi,const real &vyisoj,const real &vzisoi,const real &vzisoj);
}; // end of class TwoDTrussElement //
#endif
