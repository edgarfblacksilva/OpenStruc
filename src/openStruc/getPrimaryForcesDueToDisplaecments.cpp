#include "openStruc.h"

void OpenStruc::getPrimaryForcesDueToDisplaecments()
{
    // local variables
    intPos dx, dy, dz, rx, ry,rz;
    // end of local variables

    switch (structureType) {
        case twoDTruss:
            dx=0; dy=1;
            dz = rx = ry = rz = dofPerJoint;
            break;
        case threeDTruss:
            dx=0; dy=1; dz=2;
            rx = ry = rz = dofPerJoint;
            break;
        case grid:
            dz=0; rx=1; ry=2;
            dx = dy = rz = dofPerJoint;
            break;
        case twoDFrame:
            dx=0; dy=1,rz=2;
            dz = rx = ry = dofPerJoint;
            break;
        case threeDFrame:
            dx=0; dy=1,dz=2;rx=3;ry=4;rz=5;
            break;
        default:
            cerr << errorMessage[16] <<  getLineCounter() <<'\n'; exit(16);  
    } // end switch //

    real *d=nullptr;
    dimVec(d,dofPerElement);

    if (lineNumber + numberOfSupportDisplacement + 2 > 56) {
        header();
        cout << titleCase[loadCase] << "\n\n";
        lineNumber+=2;
    } // end if //
    jnt->printJointInfo(2);lineNumber+=2;
    
    do {
        readLine();  // this jumps empty lines  
    } while ( endcrd() ); // end do-while //    
    
    //for (auto i=one; i<=numberOfSupportDisplacement; ++i) {
    int joint;
    while (integr(joint)) {
        ++numberOfSupportDisplacement;
    
        if (lineNumber> 56) {
            header();
            cout << titleCase[loadCase] << "\n\n";
            lineNumber+=2;
            jnt->printJointInfo(2);lineNumber+=2;
        } // end if //
        
        auto jointRecNber=zero;
        jointRecNber = joint-1;
        jnt->read(jointRecNber);

        if (   jnt->getTypeOfRestriction() == 0) {
            #if defined (ENGLISH)
            cerr << "ERROR. Support displacement at unrestricted node.\n";
            cerr << "Please, chech node: " << joint << '\n';
            cout << "ERROR. Support displacement at unrestricted node.\n";
            cout << "Please, chech node: " << joint << '\n';
            #elif defined (ESPANOL)
            cerr << "ERROR. Movimiento de apoyo en junta no restringida.\n";
            cerr << "Revise la junta : " << joint << '\n';
            cout << "ERROR. Movimiento de apoyo en junta no restringida.\n";
            cout << "Revise la junta : " << joint << '\n';
            #endif  
            exit(0);
        } // end if //
        
        cout << setw(12) << joint;
        double temp;
        do {
            if( matchs_exact( "dx") ) {                
                if (dx<dofPerJoint) {
                    if (numd(temp)) {
                        jnt->setInitialDisp(temp,dx);
                    } // end if //                            
                } // end if //                    
            } else if(matchs_exact( "dy")  ) {
                if (dy<dofPerJoint) {
                    if (numd(temp)) {
                        jnt->setInitialDisp(temp,dy);
                    } // end if //                            
                } // end if //                    
            } else if(matchs_exact( "dz")  ) {
                if (dz<dofPerJoint) {
                    if (numd(temp)) {
                        jnt->setInitialDisp(temp,dz);
                    } // end if //                            
                } // end if //                    
            } else if(matchs_exact( "rx")  ) {
                if (rx<dofPerJoint) {
                    if (numd(temp)) {
                        jnt->setInitialDisp(temp,rx);
                    } // end if //                            
                } // end if //                    
            } else if(matchs_exact( "ry")  ) {
                if (ry<dofPerJoint) {
                    if (numd(temp)) {
                        jnt->setInitialDisp(temp,ry);
                    } // end if //                            
                } // end if //                    
            } else if(matchs_exact( "rz")  ) {
                if (rz<dofPerJoint) {
                    if (numd(temp)) {
                        jnt->setInitialDisp(temp,rz);
                    } // end if //                            
                } // end if //                    
            } // end if                            
        } while ( !endcrd() ); // end do-while //

        for(auto k=zero; k<dofPerJoint; ++k) {
            cout << setw(11) << setprecision(7) << jnt->getInitialDisp(k);
        } // end for //
        
        jnt->write(jointRecNber);
        cout << '\n';
        ++lineNumber;
        readLine();    
        while ( endcrd() ) {
            readLine();        // this jumps empty lines
        } // end while //
    } // end while ()  //
    
    cout << '\n';
    ++lineNumber;
    
    for(auto elementRecNber=zero; elementRecNber < numberOfElements; ++elementRecNber) {
        elm->read(elementRecNber);
        bool mytest = false;
        auto jointRecNber = elm->getElementJointI() - 1;
        // Determinacion de desplazamientos en el miembro [i]
        for(auto k=one,j=one; j<=2; ++j) {
            jnt->read(jointRecNber);        
            for(auto i=zero; i<dofPerJoint; ++i,++k) {
                d[k] = jnt->getInitialDisp(i);
                if (d[k] != 0.0) {
                    mytest = true;
                } // end if //
            } // end for //
            jointRecNber = elm->getElementJointJ() - 1 ;
        } // end for //
        
        if (mytest) { // Solo se ejecuta si el miembro tiene desplazamiento en alguno de sus extremos

            elm->mult6(d); // d[] displacements in global coordinates --> forces in local coordinates.
            
            auto elementForcesRecNber=zero;             
            if (numberOfElementCombinations > 0) {
                //elementForcesRecNber = numberOfElementCombinations * elementRecNber + loadCase -1;
                elementForcesRecNber = numberOfLoadCases * elementRecNber + loadCase -1;
            } else {
                elementForcesRecNber=elementRecNber;
            } // end if //
            
            elm->readEF(elementForcesRecNber);
            elm->setForcesInElement(static_cast<real>(true), 0);  // Flag to indicate that there is primary forces in this member
            
            for(auto k=one; k<=dofPerElement; ++k) {
                elm->addForcesInElement(d[k], k);
            } // end for //
            
            elm->writeEF(elementForcesRecNber);            
        } // end if //
    } // end for //
    freeVec(d);
    areThereLoadedElements=true;
} // end of OpenStruc::getPrimaryForcesDueToDisplaecments() //
