#include "openStruc.h"
//  the variables releasesI and releasesJ  took the role of the iar variable in the ade1 program
void OpenStruc::setStructureType(const StrucType &type, const intPos siae) {
    structureType=type;
    switch (type) {
        case twoDTruss:        
            j2dt = new TwoDTrussJoint(fileName, dofPerJoint, coordPerJoint);            
            e2dt = new TwoDTrussElement(fileName, dofPerElement,siae);
            jnt = j2dt;
            elm = e2dt;            
            //numberOfPropPerElement=3; // This could change to one because sri and srj are not part of the data included in element
            // sri, srj can have default values and not be read every time, in which case numberOfPropPerElement=1
            //prop = new real [numberOfPropPerElement]; // ar, sri, srj
            break;
        case threeDTruss:
            j3dt = new ThreeDTrussJoint(fileName, dofPerJoint, coordPerJoint);  
            e3dt = new ThreeDTrussElement(fileName, dofPerElement,siae);  
            jnt = j3dt;
            elm = e3dt;
            break;
        case grid:
            jg = new GridJoint(fileName, dofPerJoint, coordPerJoint);
            eg = new GridElement(fileName, dofPerElement, siae);
            jnt = jg;
            elm = eg;
            break;
        case twoDFrame:
            j2df = new TwoDFrameJoint(fileName, dofPerJoint, coordPerJoint);
            e2df = new TwoDFrameElement(fileName, dofPerElement, siae);
            jnt = j2df;
            elm = e2df;
            break;
        case threeDFrame:
            j3df = new ThreeDFrameJoint(fileName, dofPerJoint, coordPerJoint);
            e3df = new ThreeDFrameElement(fileName, dofPerElement, siae);
            jnt = j3df;
            elm = e3df;
            break;
        default:
            cout << "Error in Struct type.\nQuitting .....\n";
            exit(1);  
    } // end switch //
} // end of OpenStruc::setStructureType() //
