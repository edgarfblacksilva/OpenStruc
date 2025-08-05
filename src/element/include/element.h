#ifndef ELEMENT
#define ELEMENT
#include<iostream>
using std::cout;
using std::cerr;

#include <fstream>
using std::fstream;
using std::ios;

#include <cstring>
using std::string;

#include "typedef.h"
#include "lenguage.h"
#include "dimen.h"


class Element {
    public:
        Element(const string &filename);
        ~Element(); // end of Element destructor //

        void write(const intPos &rec);
        void read (const intPos &rec);
        
        void writeEF(const intPos &rec);
        void readEF (const intPos &rec);
        inline void clearForcesInElement(){ memset(forcesInElement, 0, sizeof(real)*(totalNumberOfForces+1));}
        //inline void clearForcesInElement(const intPos &index) {forcesInElement[index] = 0.0;}
        inline void setForcesInElement(const real &value, const intPos &index) {forcesInElement[index]  = value;}
        inline void addForcesInElement(const real &value, const intPos &index) {forcesInElement[index] += value;}
        inline real getForcesInElement(const intPos &index) {return forcesInElement[index];}
        inline void setGlobalTempIncrement(const real &t) {globalTempIncrement=t;}
        inline real getGlobalTempIncrement() {return globalTempIncrement;}
        
        virtual void defineSectionProperties(real *__restrict const myData, const intPos &secType, const intPos &matType,const real &e, const real &g )=0;
        virtual intPos getElementJointI()=0;
        virtual intPos getElementJointJ()=0;
        virtual void setElementEndJoints(const intPos &i, const intPos &j)=0;
        virtual real getLength()=0;
        virtual intPos getMatType()=0;
        virtual void setElementLengthAndRotation(const real *__restrict const, const real *__restrict const, real *)=0;
        virtual void getElementStiffnessFactors(real *)=0;
        virtual void getElementRotations(real *)=0;
        virtual void setElementStiffnessFactors(const real &, const real &, real , real, const bool &, const bool &, const bool & )=0;
        virtual real getAr()=0;
        virtual real getIx()=0;
        virtual real getIy()=0;
        virtual real getIz()=0;
        virtual real getBz()=0;
        virtual real getBy()=0;                
        virtual void setSectionProperties(real *)=0;
        virtual void getGlobalStiffnessMatrix(real **)=0;
        inline virtual void printElementInfo(const intPos &val) {cout << elementMessages[val];} ;
        virtual void printElementPrimaryForces(const intPos &, intPos &)=0;
        
        virtual void applyLinVarLoads(real *__restrict const d, real &axiso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, real Wxi, real Wxj, real Wyi, real Wyj, real Wzi, real Wzj, real a,const real &b)=0;
        virtual void applyUniformTorsion(real *__restrict const d, real &pariso, const real &Tx, const real &a, const real &b)=0;
        virtual void applyConcentratedMoment(real *__restrict const d, real &pariso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, const real &Px, const real &Py, const real &Pz, const real &a)=0;
        virtual void applyConcentratedLoads(real *__restrict const d, real &axiso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, const real &cx, const real &cy, const real &cz, const real &a)=0;
        virtual void applyUniformLoads(real *__restrict const d, real &axiso,real &vyisoi,real &vyisoj,real &vzisoi,real &vzisoj, const real &Wx, const real &Wy,const real &Wz, const real &a,const real &b)=0;
        virtual void applyTempGradients(real *__restrict const d,const real &ct,const real &ato1, const real &dty, const real &dtz, const real &by ,const real &bz)=0;
        virtual void finishApplingPrimaryForces(real *__restrict const d,const real &length,const real &axiso,const real &pariso,const real &vyisoi,const real &vyisoj,const real &vzisoi,const real &vzisoj)=0;
        
        static fstream elementsBinaryFile;
        static fstream elementsForcesBinaryFile;
        static intPos sizeOfElementRecord;
        static intPos sizeOfElementForcesRecord;
        
        
        inline void flipForcesInElement(const intPos &index) {forcesInElement[index] *= -1.0;}
        virtual void mult4(real *__restrict const globalForces)=0;
        virtual void mult6(real *__restrict const dg2fl)=0;
        static bool gridTypeElement;
        inline intPos getSecctionsInsideAnElement(){return secctionsInsideAnElement;}
        inline intPos getTotalNumberOfForces(){return totalNumberOfForces;}
        virtual void getLocalStiffnessMatrix(real **)=0;
        
    protected:
        static real globalTempIncrement;
        static intPos secctionsInsideAnElement; // 0 is the default value
        static intPos totalNumberOfForces;
        static string elementMessages[6]; // 0 to 5
        static real *__restrict forcesInElement;
    private:
        static string fileName1;
        static string fileName2;
}; // end of class Element
#endif
