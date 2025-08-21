#ifndef JOINT
#define JOINT
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

class Joint {
    public:
        Joint(const string &filename);                  
        ~Joint();
        
        void write(const intPos &rec);
        void read (const intPos &rec);

        void writeReac(const intPos &rec);
        void readReac (const intPos &rec);
        inline void setJointReactionsRecord(const real &value, const intPos &index) {jointReactionsRecord[index] = value;}
        inline real getJointReactionsRecord(const intPos &index) {return jointReactionsRecord[index];}
        
        virtual void setCoord(const real *__restrict const my)=0;
        virtual void getCoord(      real *__restrict const my)=0;
                
        virtual void setLoadReac(const real &val, const intPos &n)=0;
        virtual real getLoadReac(const intPos &n)=0;
        
        virtual void setSpringConstants(const real *__restrict const my)=0;
        virtual void getSpringConstants(      real *__restrict const my)=0;
        
        virtual void cleanInitialDisp()=0;

        virtual void setInitialDisp(const real &val, const intPos &index)=0;
        virtual real getInitialDisp(const intPos &)=0;

        inline virtual void printJointInfo(const intPos &val){cout << jointMessages[val];}
        
        inline void setTypeOfRestriction(const short &m)     {typeOfRestriction=m;}
        inline short getTypeOfRestriction() {return typeOfRestriction;}
                
        static fstream jointsBinaryFile;
        static intPos sizeOfJointRecord;
        static intPos sizeOfJointReactionsRecord;
    protected:
        static fstream reactionsBinaryFile;
        static string jointMessages[6]; // 0 to 5
        
        short typeOfRestriction=0;
        static real *__restrict jointReactionsRecord;
    private:
        static string fileName1;
        static string fileName2;        
        
}; // end of class Joint //
#endif
