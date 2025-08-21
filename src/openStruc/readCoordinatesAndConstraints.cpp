#include "openStruc.h"

void OpenStruc::readCoordinatesAndConstraints()
{
    // local variables
    intPos dx, dy, dz, rx, ry,rz;
    real kdx, kdy, kdz, krx, kry,krz;        
    double val;
    int jointNber;
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
    
    real *coord = new real [coordPerJoint];
    real *auxArray = new real [dofPerJoint];
    for (auto i=one; i<=numberOfNodes; ++i) {
        memset(auxArray,0,sizeof(real)*dofPerJoint);    
        readLine();            // this force the material data to be in their own line
        while ( endcrd() ) {
            readLine();        // this jumps empty lines
        } // end while //
        while (true) {
            if (integr(jointNber)) {
                --jointNber;
                jnt->setTypeOfRestriction(static_cast<short>(0));
                for (auto c=zero; c<coordPerJoint; ++c) {
                    if (numd(val)) {
                       coord[c] = static_cast<real>(val);
                    //} else if( endcrd() ) {
                    //   break; // jump out of the while loop
                    } // end if //
                } // end for //
            } else if( matchs( "support", 4 ) ) {
                ++numberOfSuppNodes;
                do {
                    if( matchs( "dx", 2 ) ) {
                        if (dx<dofPerJoint) {constraint[jointNber][dx] = true;jnt->setTypeOfRestriction(static_cast<short>(1));}
                    } else if( matchs( "dy", 2 ) ) {
                        if (dy<dofPerJoint) {constraint[jointNber][dy] = true;jnt->setTypeOfRestriction(static_cast<short>(1));}
                    } else if( matchs( "dz", 2 ) ) {                        
                        if (dz<dofPerJoint) {constraint[jointNber][dz] = true;jnt->setTypeOfRestriction(static_cast<short>(1));}
                    } else if( matchs( "rx", 2 ) ) {                        
                        if (rx<dofPerJoint) {constraint[jointNber][rx] = true;jnt->setTypeOfRestriction(static_cast<short>(1));}
                    } else if( matchs( "ry", 2 ) ) {
                        if (ry<dofPerJoint) {constraint[jointNber][ry] = true;jnt->setTypeOfRestriction(static_cast<short>(1));}
                    } else if( matchs( "rz", 2 ) ) {
                        if (rz<dofPerJoint) {constraint[jointNber][rz] = true;jnt->setTypeOfRestriction(static_cast<short>(1));}
                        
                    } else if( matchs( "kdx", 3 ) ) {
                        if (dx<dofPerJoint) {
                            if (numd(val)) {
                                auxArray[dx] = static_cast<real>(val);
                                jnt->setTypeOfRestriction(static_cast<short>(2));
                            } // end if //                            
                        } // end if //
                    } else if( matchs( "kdy", 3 ) ) {
                        if (dy<dofPerJoint) {
                            if (numd(val)) {
                                auxArray[dy] = static_cast<real>(val);
                                jnt->setTypeOfRestriction(static_cast<short>(2));
                            } // end if //                            
                        } // end if //
                    } else if( matchs( "kdz", 3 ) ) {
                        if (dz<dofPerJoint) {
                            if (numd(val)) {
                                auxArray[dz] = static_cast<real>(val);
                                jnt->setTypeOfRestriction(static_cast<short>(2));
                            } // end if //                            
                        } // end if //
                    } else if( matchs( "krx", 3 ) ) {
                        if (rx<dofPerJoint) {
                            if (numd(val)) {
                                auxArray[rx] = static_cast<real>(val);
                                jnt->setTypeOfRestriction(static_cast<short>(2));
                            } // end if //                            
                        } // end if //
                    } else if( matchs( "kry", 3 ) ) {
                        if (ry<dofPerJoint) {
                            if (numd(val)) {
                                auxArray[ry] = static_cast<real>(val);
                                jnt->setTypeOfRestriction(static_cast<short>(2));
                            } // end if //                            
                        } // end if //
                    } else if( matchs( "krz", 3 ) ) {
                        if (rz<dofPerJoint) {
                            if (numd(val)) {
                                auxArray[rz] = static_cast<real>(val);
                                jnt->setTypeOfRestriction(static_cast<short>(2));
                            } // end if //                            
                        } // end if //
                    } // end if //
                } while ( !endcrd() ); // end do-while //
            } else if( endcrd() ) {
               break; // jump out of the while loop
            } // end if //  
        } // end while //        
        jnt->setCoord(coord);
        jnt->setSpringConstants(auxArray);
        jnt->write( static_cast<intPos>(jointNber) );
    } // end for //
    delete [] coord;
    delete[] auxArray;    
} // end of OpenStruc::readCoordinatesAndConstraints() //
