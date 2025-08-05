#include "openStruc.h"

void OpenStruc::readSectionTypes(real **(&sectionTypes))
{    
    dimMat(sectionTypes, numberOfSectionTypes,static_cast<intPos>(9)); // there are 8+1 section Properties, 6 of which will be stored in element record
    intPos matType=1, secType=3;
    double val;
    int iVal;
    for (auto i=one; i<=numberOfSectionTypes; ++i) {    
        readLine();            // this force the material data to be in their own line
        while ( endcrd() ) {
            readLine();        // this jumps empty lines
        } // end while //
        while (true) {
            if ( matchs("b", 1) ) {
                if (numd(val)) {
                   sectionTypes[i][1] = static_cast<real>(val);
                   secType = 1;
                } // end if //
            } else if ( matchs("d", 1) ) {
                if (numd(val)) {
                   sectionTypes[i][1] = static_cast<real>(val);
                   secType = 2;
                } // end if //
            } else if (matchs("ar", 2) ) {
                if (numd(val)) {
                   sectionTypes[i][1] = static_cast<real>(val);
                } // end if //
            } else if(matchs("h", 1) ) {
                if (numd(val)) {
                   sectionTypes[i][2] = static_cast<real>(val);
                   secType = 1;
                } // end if //
            } else if(matchs("Ix", 2) ) {
                if (numd(val)) {
                   sectionTypes[i][2] = static_cast<real>(val);
                } // end if //
            } else if(matchs("Iy", 2)) {
                if (numd(val)) {
                   sectionTypes[i][3] = static_cast<real>(val);
                } // end if //
            } else if(matchs("Iz", 2)) {
                if (numd(val)) {
                   sectionTypes[i][4] = static_cast<real>(val);
                } // end if //        
            } else if(matchs("mt", 2)) {
                if (integr(iVal)) {
                    matType= static_cast<intPos>(iVal);
                } // end if //        
            } else if( endcrd() ) {
                break; // jump out of the while loop
            } // end if //
        } // end while //
        
        elm->defineSectionProperties(&sectionTypes[i][1], secType,matType,e[matType],g[matType] );        
    } // end for //
} // end of OpenStruc::readSectionTypes() //
