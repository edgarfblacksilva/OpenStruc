#include "openStruc.h"

void OpenStruc::readLoadCases()
{
    matchs_exact("case");
    int iVal;
    
    if (integr(iVal)) {
        loadCase = static_cast<intPos>(iVal);        
        memset(&loadVector[1], 0, numberOfEqations*sizeof(real));  // cleaning the load vector
        elm->setGlobalTempIncrement(0.0);
        numberOfSupportDisplacement=zero;
        
        setElementsForcesBinaryFile();        
        areThereLoadedElements=false;
        
        if( loadCase > 0 and loadCase <= numberOfLoadCases ) {
            /*
            do {
                readLine();        // this jumps empty lines
            } while ( endcrd() ); // end do-while //
            */
            if( isstring() ) {
                positiveInt nchars; 
                char text[120];
                scan_contents( text, nchars );
                titleCase[loadCase] = text;
            } // end if //
            header();
            cout << "    " << titleCase[loadCase] << "\n\n";
            lineNumber+=2;
            
            readLine();
            while ( !matchs_exact("solve") ) {
                while ( endcrd() ) {
                    readLine();        // this jumps empty lines
                } // end while //
                if ( matchs_exact("loaded")  ) {
                    if ( matchs( "nodes",3) ) {
                        getNodalLoads();
                    } else if ( matchs( "elements", 4) ) {
                        getPrimaryForcesDueToLoads();
                        //cerr << "en file: " << __FILE__ << ", line: " << __LINE__ << '\n'; exit(0);
                    } else {
                        cerr << errorMessage[11] << getLineCounter() << '\n'; exit(11);
                    } // end if //
                } else if ( matchs_exact("global") and matchs( "temperature", 4) and matchs( "change",5 )  ) {                
                    double val;
                    if( numd(val)) {
                        elm->setGlobalTempIncrement(static_cast<real>(val));
                        #if defined (ENGLISH)
                        cout << fixed 
                             << "    Global Temperature Gradient: " << setw(6) << setprecision (3) << elm->getGlobalTempIncrement() << "\n\n";
                        #elif defined (ESPANOL)
                        cout << fixed 
                             << "    Gradiente de tempetatura global: " << setw(6) << setprecision (3) << elm->getGlobalTempIncrement() << "\n\n";
                        #endif  
                        lineNumber+=2;                        
                        if (elm->getGlobalTempIncrement() != 0.0 and !elm->gridTypeElement ) {
                            getPrimaryForcesDueToGlobalTemp();
                        } // end if //
                    } else {
                        cerr << errorMessage[13] << getLineCounter() << '\n'; exit(13);
                    } // end if //
                } else if ( matchs("support", 4) and matchs( "displacement", 4)   ) {
                    getPrimaryForcesDueToDisplaecments();
                } // end if //
            } // end while //
        } else {
            cerr << errorMessage[14] << getLineCounter() << '\n'; exit(14);
        } // end if //
    } else {
        cerr << errorMessage[12] << getLineCounter() << '\n'; exit(12);
    } // end if     
} // end of OpenStruc::readLoadCases() //
