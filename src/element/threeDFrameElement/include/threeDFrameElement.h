#ifndef THREEDFRAMEELEMENT
#define THREEDFRAMEELEMENT

#include "element.h"

class ThreeDFrameElement : public Element 
{
    public:
        ThreeDFrameElement(const string &filename, intPos &DofPerElement, const intPos &siae = 0);
        ThreeDFrameElement(const string &filename);
        ~ThreeDFrameElement() {;} // end of ThreeDFrameElement destructor //
        
        virtual void getGlobalStiffnessMatrix(real **);
        virtual void getLocalStiffnessMatrix(real **);

    private:
        inline real getAr(){return properties[0];}            
        inline real getIx(){return properties[1];}
        inline real getIy(){return properties[2];}
        inline real getIz(){return properties[3];}
        inline real getBz(){return properties[4];}
        inline real getBy(){return properties[5];}
        virtual void setSectionProperties(real *);
        virtual void setElementLengthAndRotation(const real *__restrict const,const real *__restrict const, real *);
        inline virtual void getElementStiffnessFactors(real *__restrict const my) { memcpy(my, stiffnessFactors, sizeof(real)*7);}
        inline virtual void getElementRotations(real *__restrict const my) { memcpy(my, r, sizeof(real)*9);}
        virtual void setElementStiffnessFactors(const real &, const real &, real , real, const bool &, const bool &, const bool & );
        inline virtual intPos getMatType(){return materialType;}
        inline virtual intPos getElementJointI(){return jointI;}
        inline virtual intPos getElementJointJ(){return jointJ;}
        inline virtual void setElementEndJoints(const intPos &i, const intPos &j){jointI=i;jointJ=j;}
        virtual void defineSectionProperties(real *__restrict const myData, const intPos &secType, const intPos &matType,const real &e, const real &g );
        virtual void printElementPrimaryForces(const intPos &, intPos &);
    protected:
        static constexpr intPos dofPerElement {12};
        virtual void mult4(real *__restrict const globalForces);
        void mult4(real *__restrict const w, const real *__restrict const d);
        virtual void mult6(real *__restrict const dg2fl);
        inline virtual real getLength() {return length;}
        virtual void applyLinVarLoads(real *__restrict const d, real &axiso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, real Wxi, real Wxj, real Wyi, real Wyj, real Wzi, real Wzj, real a,const real &b);
        virtual void applyUniformTorsion(real *__restrict const d, real &pariso, const real &Tx, const real &a, const real &b); 
        virtual void applyConcentratedMoment(real *__restrict const d, real &pariso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, const real &cx,const real &cy,const real &cz, const real &a);
        virtual void applyConcentratedLoads(real *__restrict const d, real &axiso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, const real &cx, const real &cy, const real &cz, const real &a);
        virtual void applyUniformLoads(real *__restrict const d, real &axiso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, const real &Wx, const real &Wy, const real &Wz, const real &a,const real &b);
        virtual void applyTempGradients(real *__restrict const d, const real &ct, const real &ato1, const real &dty, const real &dtz, const real &by ,const real &bz);
        virtual void finishApplingPrimaryForces(real *__restrict const d,const real &length,const real &axiso,const real &pariso,const real &vyisoi,const real &vyisoj,const real &vzisoi,const real &vzisoj);

        intPos jointI,jointJ;
        intPos materialType;
        real length;        
        real properties[6]       = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; // ar*E/L , Ix, Iy, Iz, bz, by
        real r[9]                = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        real stiffnessFactors[7] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};        
}; // end of class ThreeDFrameElement //
#endif
