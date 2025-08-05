#include "openStruc.h"

void OpenStruc::printElementsSolution() 
{
    real *d=nullptr;
    dimVec(d,elm->getTotalNumberOfForces());
    
    elm->clearForcesInElement();
    
    elm->printElementInfo(3);lineNumber+=2;
    
    for(auto elementRecNber=zero; elementRecNber<numberOfElements; ++elementRecNber) {
    
        if (elm->getSecctionsInsideAnElement() == 0 and lineNumber > 56) {
            header();
            cout << titleCase[loadCase] << "\n\n";
            lineNumber+=2;
            elm->printElementInfo(3);lineNumber+=2;
        } else if (elm->getSecctionsInsideAnElement() > 0 and lineNumber > 53) {
            header();
            cout << titleCase[loadCase] << "\n\n";
            lineNumber+=2;
            elm->printElementInfo(3);lineNumber+=2;
        } // end if //
        elm->read(elementRecNber);
        
        // selecting global disp related to joints i and j in this element
        auto k =  (elm->getElementJointI() -1)*dofPerJoint + 1;
        auto kk = (elm->getElementJointJ() -1)*dofPerJoint + 1;
        
        for(auto i=one; i<=dofPerJoint; ++i,++k,++kk) {
            d[i]             = loadVector[k];
            d[i+dofPerJoint] = loadVector[kk];
        } // end for //
           
        // end of selecting global disp related to joints i and j in this element
        elm->mult6(d); // d[] displacements in global coordinates --> forces in local coordinates.

        auto elementForcesRecNber=zero;             
        if (numberOfElementCombinations > 0) {
            elementForcesRecNber = numberOfLoadCases * elementRecNber + loadCase -1;
            //elementForcesRecNber = numberOfElementCombinations * elementRecNber + loadCase -1;
        } else {
            elementForcesRecNber=elementRecNber;
        } // end if //
        
        for(auto i=(one + dofPerElement); i<=elm->getTotalNumberOfForces(); ++i) {
            d[i] = 0.0;
        } // end for //
        
        elm->readEF(elementForcesRecNber);
        
        for(auto i=one; i<=elm->getTotalNumberOfForces(); ++i) {
            d[i] += elm->getForcesInElement(i);
        } // end for //
        
        switch (structureType) {
        case twoDTruss:        
            d[1] *= -1;
            d[4] *= -1;
            break;
        case threeDTruss:
            d[1] *= -1;
            d[5] *= -1;
            d[6] *= -1;
            break;
        case grid:
            d[2] *= -1;
            d[4] *= -1;
            d[6] *= -1;
            break;
        case twoDFrame:
            d[1] *= -1;
            d[3] *= -1;
            d[5] *= -1;
            break;
        case threeDFrame:
            d[ 1] *= -1;
            d[ 4] *= -1;
            d[ 6] *= -1;
            ///////////
            d[ 8] *= -1;
            d[ 9] *= -1;
            d[11] *= -1;
            break;
        } // end switch //
        real segment = elm->getLength()/(elm->getSecctionsInsideAnElement() + 1);
        
        for(auto i=dofPerElement, ii=one; ii<=elm->getSecctionsInsideAnElement(); ++ii) {
            switch (structureType) {
            case twoDTruss:        
                d[++i] += d[1];
                d[++i] += d[2];
                break;
            case threeDTruss:
                d[++i] += d[1];
                d[++i] += d[2];
                d[++i] += d[3];
                break;
            case grid:
                d[++i] += d[1];
                d[++i] += d[2];
                d[++i] += (d[3]+d[1]*ii*segment);
                break;
            case twoDFrame:
                d[++i] += d[1];
                d[++i] += d[2];
                d[++i] += (d[3]+d[2]*ii*segment);
                break;
            case threeDFrame:
                d[++i] += d[1];
                d[++i] += d[2];
                d[++i] += d[3];
                d[++i] += d[4];
                d[++i] += (d[5]+d[3]*ii*segment);
                d[++i] += (d[6]+d[2]*ii*segment);
                break;
            } // end switch //
        } // end for //
        cout << fixed <<setw(11) << elementRecNber+1 << setw(6) <<  elm->getElementJointI() << setw(8) << setprecision(3) << 0.0;
        for(auto i=one; i<=dofPerJoint; ++i) {
            cout << setw(11) << d[i];
        } // end for //
        cout << '\n';
        ++lineNumber;
                
        if (elm->getSecctionsInsideAnElement()  > 0) {
            auto kk = one + dofPerElement;
            for(auto k=one; k<=elm->getSecctionsInsideAnElement(); ++k) {
                cout << setw(25) << segment*k;
                for(auto i=one; i<=dofPerJoint; ++i,++kk) {
                    cout <<  setw(11) << d[kk];
                } // end for //
                cout << '\n';
            } // end for //
            lineNumber += elm->getSecctionsInsideAnElement();
        } // end if //
        
        cout << setw(17) << elm->getElementJointJ() << setw(8)  << elm->getLength(); 
        for(auto i=dofPerJoint+1; i<=dofPerElement; ++i) {
            cout << setw(11) << d[i];
        } // end for //
        cout << '\n';
        ++lineNumber;
        
        for(auto i=one; i<=elm->getTotalNumberOfForces(); ++i) {
            elm->setForcesInElement(d[i],i);
        } // end for //

        elm->writeEF(elementForcesRecNber);
    } // end for //
    cout << '\n';
    ++lineNumber;
    
    // Calculo de las reacciones
    
    memset(&loadVector[1], 0, numberOfEqations*sizeof(real));  // cleaning the load vector

    for(auto elementRecNber=zero; elementRecNber<numberOfElements; ++elementRecNber) {
        elm->read(elementRecNber);
    
        auto elementForcesRecNber=zero;             
        if (numberOfElementCombinations > 0) {
            elementForcesRecNber = numberOfLoadCases * elementRecNber + loadCase -1;
            //elementForcesRecNber = numberOfElementCombinations * elementRecNber + loadCase -1;
        } else {
            elementForcesRecNber=elementRecNber;
        } // end if //
        elm->readEF(elementForcesRecNber);

        switch (structureType) {
        case twoDTruss:        
            elm->flipForcesInElement(1);
            elm->flipForcesInElement(4);
            break;
        case threeDTruss:
            elm->flipForcesInElement(1);
            elm->flipForcesInElement(5);
            elm->flipForcesInElement(6);
            break;
        case grid:
            elm->flipForcesInElement(2);
            elm->flipForcesInElement(4);
            elm->flipForcesInElement(6);
            break;
        case twoDFrame:
            elm->flipForcesInElement(1);
            elm->flipForcesInElement(3);
            elm->flipForcesInElement(5);
            break;
        case threeDFrame:
            elm->flipForcesInElement(1);
            elm->flipForcesInElement(4);
            elm->flipForcesInElement(6);
            ///////////
            elm->flipForcesInElement(8);
            elm->flipForcesInElement(9);
            elm->flipForcesInElement(11);
            break;
        } // end switch //
        
        elm->mult4(d); // now d has the reactions in global coordinates
        
        // selecting global disp related to joints i and j in this element
        auto k =  (elm->getElementJointI() -1)*dofPerJoint + 1;
        auto kk = (elm->getElementJointJ() -1)*dofPerJoint + 1;
        
        for(auto i=one; i<=dofPerJoint; ++i, ++k, ++kk) {
            loadVector[k]  += d[i];
            loadVector[kk] += d[i+dofPerJoint];            
        } // end for //
        // end of selecting global disp related to joints i and j in this element
        
    } // end for //
    freeVec(d);
} // end of OpenStruc::printElementsSolution() //
