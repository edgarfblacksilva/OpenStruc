#include "openStruc.h"

void OpenStruc::defineElements(real **sectionTypes)
{
    real coordI[3];
    real coordJ[3];
    real *pointP=nullptr; // set the pointer to Null if there is no point P

    intPos secType;
    intPos ji,jj;
    intPos elementNber;
    int iVal;
    double val;

    int intlst[100],errCode; // variables used by the trlist() method
    intPos listSize;

    auto i = zero;
    while (i<numberOfElements ) {
        real islI=0.0;
        real islJ=0.0;
        bool releasesI=false;
        bool releasesJ=false;
        if ( structureType == twoDTruss or structureType == threeDTruss) {
            releasesI=releasesJ=true;
        } // end if //

        do {
            readLine();        // this force the material data to be in their own line ans  jumps empty lines
        } while ( endcrd() );
        
        trlist(intlst,sizeof(intlst)/sizeof(int),numberOfElements,listSize,errCode);

        if (errCode == 4) {
            //cerr << errorMessage[21] <<  getLineCounter() <<'\n'; exit(21);
            break;
        } // end if //

        int iplist {1}; // variables used to test trxlst() method
        do {
            trxlst(iVal, iplist, intlst,listSize);
            ++i;

            elementNber=static_cast<intPos>(iVal-1);
            elm->read(elementNber);
            ji=elm->getElementJointI();
            jj=elm->getElementJointJ();
            
            // this line originally was in readIncidences()
            formLeftColumn(ji,jj); // this line originally was in readIncidences()
            // this line originally was in readIncidences()
            
            jnt->read(ji-1);
            jnt->getCoord(coordI);
            jnt->read(jj-1);
            jnt->getCoord(coordJ);

            while (true) {
                if( matchs( "secType", 4 ) ) {
                    if (integr(iVal)) { // reading section type
                        secType=static_cast<intPos>(iVal);
                        if (secType > numberOfSectionTypes) {
                            cerr << errorMessage[10] << getLineCounter() << '\n'; exit(0);    
                        } // end if
                    } // end if //
                } else if (matchs( "release", 4 )) {    
                    if ( matchs_exact( "mzi" ) ) {
                        releasesI=true;
                    } else if( matchs_exact( "mzj" ) )  {
                        releasesJ=true;
                    } // end if //
                } else if (matchs_exact( "isl_i" )) { 
                
                    if ( numd(val) ) {
                        islI= static_cast<real> (val);
                    } else  {
                        cerr <<  errorMessage[13] << getLineCounter() << '\n';
                    } // end if //
                } else if (matchs_exact( "isl_j" )) { 
                    if ( numd(val) ) {
                        islJ= static_cast<real> (val);
                    } else  {
                        cerr <<  errorMessage[13] << getLineCounter() << '\n';
                    } // end if //
                } else if (matchs_exact( "rPoint" )) {
                    pointP=new real[3];
                    if ( numd(val) ) {
                        pointP[0] = static_cast<real> (val);
                    } else {
                        cerr << "In defining rPoint " << errorMessage[13] << getLineCounter() << '\n'; exit(0);
                    } // end if //

                    if ( numd(val) ) {
                        pointP[1] = static_cast<real> (val);
                    } else {
                        cerr << "In defining rPoint " << errorMessage[13] << getLineCounter() << '\n'; exit(0);
                    } // end if //

                    if ( numd(val) ) {
                        pointP[2] = static_cast<real> (val);
                    } else {
                        cerr << "In defining rPoint " << errorMessage[13] << getLineCounter() << '\n'; exit(0);
                    } // end if //
                } else if( endcrd() ) {
                    break; // jump out of the while loop
                } else  {
                    cerr << errorMessage[11] << getLineCounter() << '\n'; 
                    doScan();
                } // end if //
            } // end while //
            
            elm->setElementLengthAndRotation(coordI, coordJ, pointP);
            elm->setSectionProperties(&sectionTypes[secType][1]);
            elm->setElementStiffnessFactors(sectionTypes[secType][7], sectionTypes[secType][8],islI,islJ, shearDeformation, releasesI,releasesJ);
            elm->write(elementNber);
            if (pointP != nullptr) {
                delete[] pointP; 
                pointP=nullptr;
            } // end if //            
        } while(iplist != 0); // end do-while()        
    } // end for //
    
    if ( i < numberOfElements ) { // reading element number
        cerr << errorMessage[22] << getLineCounter() << '\n'; exit(0);        
    }  // end if // 
    
} // end of OpenStruc::defineElements() //
