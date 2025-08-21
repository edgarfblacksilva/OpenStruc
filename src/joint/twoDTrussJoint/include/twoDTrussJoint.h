#ifndef TWODTRUSSJOINT
#define TWODTRUSSJOINT

#include "joint.h"

class TwoDTrussJoint: public Joint {
    public:
        TwoDTrussJoint(const string &filename, intPos &, intPos &);
        ~TwoDTrussJoint() {;} // end of TwoDTrussJoint destructor //;       

        inline virtual void setCoord(const real *__restrict const my){ memcpy(coordinates, my, sizeof(real)*coordPerJoint);}
        inline virtual void getCoord(      real *__restrict const my){ memcpy(my, coordinates, sizeof(real)*coordPerJoint);}        
         
        inline virtual void setLoadReac(const real &val, const intPos &n) {load4Reac[n]=val;}
        inline virtual real getLoadReac(const intPos &n) {return load4Reac[n];}         
        
        inline virtual void setSpringConstants(const real *__restrict const my){ memcpy(springConstants, my, sizeof(real)*dofPerJoint);}
        inline virtual void getSpringConstants(      real *__restrict const my){ memcpy(my, springConstants, sizeof(real)*dofPerJoint);}

        inline virtual void cleanInitialDisp() { memset(initialDisp, 0, sizeof(real)*dofPerJoint);}

        inline virtual void setInitialDisp(const real &val, const intPos &index){initialDisp[index]=val;}
        inline virtual real getInitialDisp(const intPos &index){return initialDisp[index];}

    private:
        static constexpr intPos dofPerJoint   {2};
        static constexpr intPos coordPerJoint {2};
           
        real initialDisp    [dofPerJoint]   = {0.0,0.0};
        real load4Reac      [dofPerJoint]   = {0.0,0.0};
        real springConstants[dofPerJoint]   = {0.0,0.0};
        real coordinates    [coordPerJoint] = {0.0,0.0};
}; // end of class TwoDTrussJoint //
#endif
