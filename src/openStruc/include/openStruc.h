#ifndef OPENSTRUC_H
#define OPENSTRUC_H


#include <iostream>
using std::ostream;

#include <iomanip>
using std::setprecision;
using std::fixed;
using std::scientific;
using std::uppercase;

#include "typedef.h"
#include "lenguage.h"
#include "solver.h"

#include "joint.h"
#include "twoDFrameJoint.h"
#include "threeDFrameJoint.h"
#include "gridJoint.h"
#include "twoDTrussJoint.h"
#include "threeDTrussJoint.h"

#include "element.h"
#include "twoDFrameElement.h"
#include "threeDFrameElement.h"
#include "gridElement.h"
#include "twoDTrussElement.h"
#include "threeDTrussElement.h"



#define LINEWITH 256
#define MAXTK    30

typedef enum  {twoDTruss=1, threeDTruss, grid, twoDFrame, threeDFrame} StrucType;

#include "ObjectScan.h" // positiveInt type is defined in ObjectScan
#include "dimen.h"
//#include "matVecMult.h"
//#include "gaussElimination.h"


class OpenStruc : public Scan {
public:
    OpenStruc();
    ~OpenStruc();
    
    

    void driver();
    void setWorkingFileName(const char *);
    
private:

    inline real getOpenStrucVersion(){return OpenStrucVersion/100.0;}

    inline void setShearDeformation(){shearDeformation=true;}
    inline void unSetShearDeformation(){shearDeformation=false;}
    inline bool getShearDeformation(){ return shearDeformation;}
    
    inline StrucType getStructureType() {return structureType;}
    inline void setNumberOfNodes(const intPos &n){numberOfNodes=n;}
    inline void setNumberOfElements(const intPos &n){numberOfElements=n;}
    inline void setNumberOfMaterials(const intPos &n){numberOfMaterials=n;}
    //inline void setNumberOfSuppNodes(const intPos &n){numberOfSuppNodes=n;}
    inline void setNumberOfLoadCases (const intPos &n){numberOfLoadCases=n;}
    inline void setNumberOfSectionTypes (const intPos &n){numberOfSectionTypes=n;}
    
    inline void setNumberOfElementCombinations (const intPos &n){numberOfElementCombinations=n;}
    inline void setNumberOfNodeCombinations (const intPos &n){numberOfNodeCombinations=n;}



    void assembleGlobalStifnessMatrix();
    void combineLoadCases();
    void defineElements(real **sectionTypes);
    void finishLoadVector();    
    void formLeftColumn(const intPos &, const intPos &);
    void getNodalLoads();
    void getPrimaryForcesDueToDisplaecments();
    void getPrimaryForcesDueToGlobalTemp();
    void getPrimaryForcesDueToLoads();
    void getTitle();
    void header();
    void setHeaderMessages();    
    void printElementsSolution();
    void printJointDisplacements();
    void printJointsSolution();
    void printStrucData();
    void plotStruc();
    void readCoordinatesAndConstraints();
    void readIncidences();
    void readLoadCases();
    void readMaterials();
    void readSectionTypes(real **(&sectionTypes));
    void setBasicData();
    void setElementsForcesBinaryFile();
    void setStructureType(const StrucType &st, const intPos siae=0);
    void solveDisplacements();
    void welcomeBanner(ostream &);


    
    intPos numberOfNodes=zero;
    intPos numberOfSuppNodes=zero;
    intPos numberOfElements=zero;
    intPos numberOfMaterials=zero;
    intPos numberOfSectionTypes=zero;
    
    intPos numberOfLoadCases=zero;            // default valid value
    intPos numberOfElementCombinations=zero;  // default valid value 
    intPos numberOfNodeCombinations=zero;     // default valid value
    
    intPos coordPerJoint=zero;
    intPos dofPerElement=zero;
    intPos dofPerJoint=zero;
    intPos numberOfEqations=zero;
    
    intPos loadCase=zero;                     // default valid value
    
    //intPos numberOfLoadedNodes=zero;
    //intPos numberOfLoadedElements=zero;
    intPos numberOfSupportDisplacement = zero;
    
    intPos pageNumber=one; 
    intPos lineNumber=one;
    //real   globalTempIncrement=0.0;
    
    StrucType structureType;
    
    static constexpr intPos OpenStrucVersion = 100;
    intPos NumberOfErrorMesages;

    intPos *leftCol=nullptr;
    bool shearDeformation = false;
    bool areThereLoadedElements;

    
    void setErrorMassages();
    
    
    bool **constraint=nullptr;
    string *errorMessage=nullptr;
    string *titleCase=nullptr, *titleHip=nullptr;
    string *headerMessage=nullptr;
    string ProblemTitle;
    real **structureStiffnessMatrix=nullptr;
    real *loadVector=nullptr;
    
    
    
    real *e=nullptr, *g=nullptr, *ct=nullptr, *weight=nullptr;
    
    
    string fileName;
    bool GlobalKIsNotReduce = true;
    
    /*
    struct logical {
        bool isGlobalKDone : 1;
    }; // up to eight logical variables in one byte;    
    */
    
    Joint *jnt=nullptr;
    // Basic Joint Types 
    TwoDTrussJoint *j2dt   = nullptr;
    ThreeDTrussJoint *j3dt = nullptr;
    GridJoint  *jg         = nullptr;
    TwoDFrameJoint *j2df   = nullptr;
    ThreeDFrameJoint *j3df = nullptr;
    // end of Basic Joint Types 
    
    Element *elm=nullptr;
    // Basic Element Types 
    TwoDTrussElement *e2dt   = nullptr;
    ThreeDTrussElement *e3dt = nullptr;
    GridElement  *eg         = nullptr;
    TwoDFrameElement *e2df   = nullptr;
    ThreeDFrameElement *e3df = nullptr;
    // end of Basic Element Types 
};
#endif  // OPENSTRUC_H
