#include "openStruc.h"

void OpenStruc::getNodalLoads()
{
    // local variables
    intPos jointNber;    
    real *auxArray = new real [dofPerJoint]();
    intPos fx, fy, fz, mx, my, mz;
    int iVal;
    double val;
    // end of local variables
    
    switch (structureType) {
        case twoDTruss:
            fx=0; fy=1;
            fz = mx = my = mz = dofPerJoint;
            break;
        case threeDTruss:
            fx=0; fy=1; fz=2;
            mx = my = mz = dofPerJoint;
            break;
        case grid:
            fz=0; mx=1; my=2;
            fx = fy = mz = dofPerJoint;
            break;
        case twoDFrame:
            fx=0; fy=1, mz=2;
            fz = mx = my = dofPerJoint;
            break;
        case threeDFrame:
            fx=0; fy=1,fz=2;mx=3;my=4;mz=5;
            break;
        default:
            cerr << errorMessage[16] <<  getLineCounter() <<'\n'; exit(16);  
    } // end switch //
    
    if (lineNumber > 56) {
        header();
        cout << titleCase[loadCase] << "\n\n";
        lineNumber+=2;
        jnt->printJointInfo(1);lineNumber+=2;
    } else {
        jnt->printJointInfo(1);lineNumber+=2;        
    } // end if //

    do {
        readLine();  // this jumps empty lines  
    } while ( endcrd() ); // end do-while //    
    

    int intlst[100],errCode; // variables used by the trlist() method
    intPos listSize;
    int iplist {1}; // variables used to test trxlst() method

    do {
        trlist(intlst,sizeof(intlst)/sizeof(int),numberOfNodes,listSize,errCode);
        if (errCode == 4) {
            //cerr << errorMessage[21] <<  getLineCounter() <<'\n'; exit(21);
            break;
        } // end if //
        
        iplist=1;
        do {
            trxlst(iVal, iplist, intlst,listSize);
            
            if (lineNumber > 56) {
                header();
                cout << titleCase[loadCase] << "\n\n";
                lineNumber+=2;
                jnt->printJointInfo(1);lineNumber+=2;
            } // end if //
            auto bckSpc=zero;
            jointNber = static_cast<intPos>(iVal);
            cout << setw(8) << jointNber;
            --jointNber;
            auto idx=jointNber*dofPerJoint+1;
            do {
                if( matchs_exact( "fx") ) {
                    if (fx<dofPerJoint) {
                        if (numd(val)) {
                            loadVector[idx+fx] = static_cast<real>(val);
                            bckSpc+=2;
                        } // end if //                            
                    } // end if //                    
                } else if(matchs_exact( "fy")  ) {
                    if (fy<dofPerJoint) {
                        if (numd(val)) {
                            loadVector[idx+fy] = static_cast<real>(val);
                            bckSpc+=2;
                        } // end if //                            
                    } // end if //                    
                
                } else if(matchs_exact( "fz")  ) {
                    if (fz<dofPerJoint) {
                        if (numd(val)) {
                            loadVector[idx+fz] = static_cast<real>(val);
                            bckSpc+=2;
                        } // end if //                            
                    } // end if //                    
                } else if(matchs_exact( "mx")  ) {
                    if (mx<dofPerJoint) {
                        if (numd(val)) {
                            loadVector[idx+mx] = static_cast<real>(val);
                            bckSpc+=2;
                        } // end if //                            
                    } // end if //                    
                } else if(matchs_exact( "my")  ) {
                    if (my<dofPerJoint) {
                        if (numd(val)) {
                            loadVector[idx+my] = static_cast<real>(val);
                            bckSpc+=2;
                        } // end if //                            
                    } // end if //                    
                } else if(matchs_exact( "mz")  ) {
                    if (mz<dofPerJoint) {
                        if (numd(val)) {
                            loadVector[idx+mz] = static_cast<real>(val);
                            bckSpc+=2;
                        } // end if //                            
                    } // end if //                    
                } // end if                
            } while ( !endcrd() ); // end do-while //

            auto k=jointNber*dofPerJoint+1;
            
            for(auto i=zero; i<dofPerJoint; ++i, ++k) {
                cout << setw(11) << setprecision(3) << loadVector[k];
            } // end for //
            cout << '\n'; ++lineNumber;
            
            jnt->read(jointNber);
            jnt->getSpringConstants(auxArray);
            
            if ( jnt->getTypeOfRestriction() > 0 ) {
            
                k=jointNber*dofPerJoint+1;
                for(auto i=zero; i<dofPerJoint; ++i, ++k) {
                    if (constraint[jointNber][i] or auxArray[i] > 0.0 ) {
                        jnt->setLoadReac(-loadVector[k],i);
                    } // end if //
                } // end for //
            } // end if //
            jnt->write(jointNber);

            backsp(bckSpc);            
        } while(iplist != 0); // end do-while()
        
        do {
            readLine();  // this jumps empty lines  
        } while ( endcrd() ); // end do-while //    
            
    } while (true);
    cout << '\n'; ++lineNumber;
   delete[] auxArray; 
} // end of OpenStruc::getNodalLoads() //
