#include "openStruc.h"
    //cerr << "in file: " << __FILE__  << ", function: " << __func__ << ", line: " << __LINE__ << '\n'; exit(0);
void OpenStruc::driver()
{

    welcomeBanner(cerr);
    real **sectionTypes=nullptr;
    
    if (!isStdoutScreen()) {
       welcomeBanner(cerr);
    } // end if
    
    getTitle();
    intPos  secctionsInsideAnElement {0}; // means element divided in 1 segments
    int temp;
    while (readLine()) {        
    
        if (matchs_exact("stop")  or matchs_exact("quit")  or matchs_exact("exit")) {
            // stop, quit, exit command
            break;  // jump out of the while loop      
        } else if( matchs( "type",4 ) ) {
          // input from a different file
            if ( matchs( "plane",4) )  {
                if ( matchs( "truss",4) )  {
                    if ( matchs( "sections",5) )  {
                        if ( numi( temp ) ) {
                            secctionsInsideAnElement=static_cast<intPos>(temp-1);
                        } // end if //    
                    } // end if //    
                    setStructureType(twoDTruss,secctionsInsideAnElement); 
                } else if(matchs( "frame",4)) {
                    if ( matchs( "sections",5) )  {
                        if ( numi( temp ) ) {
                            secctionsInsideAnElement=static_cast<intPos>(temp-1);
                        } // end if //    
                    } // end if //    
                    setStructureType(twoDFrame,secctionsInsideAnElement); 
                } else if (!endcrd()) { 
                    cout << "    command not recognized....\n";
                } // end if //
            } else if (matchs("space",4)) {
                if ( matchs( "truss",4) )  {
                    if ( matchs( "sections",5) )  {
                        if ( numi( temp ) ) {
                            secctionsInsideAnElement=static_cast<intPos>(temp-1);
                        } // end if //    
                    } // end if //    
                    setStructureType(threeDTruss,secctionsInsideAnElement); 
                } else if(matchs( "frame",4)) {
                    if ( matchs( "sections",5) )  {
                        if ( numi( temp ) ) {
                            secctionsInsideAnElement=static_cast<intPos>(temp-1);
                        } // end if //    
                    } // end if //    
                    setStructureType(threeDFrame,secctionsInsideAnElement); 
                    //Debug();
                } else if (!endcrd()) { 
                    cout << "    command not recognized....\n";
                } // end if //                            
            } else if (matchs("grid",4)) {
                if ( matchs( "sections",5) )  {
                    if ( numi( temp ) ) {
                        secctionsInsideAnElement=static_cast<intPos>(temp-1);
                    } // end if //    
                } // end if //    
                setStructureType(grid,secctionsInsideAnElement);             
            } else if (!endcrd()) { 
               cout << "    command not recognized....\n";
            } // end if //        
        } else if( matchs( "number", 4 ) ) { 
            setBasicData();
        } else if( matchs( "shear", 4 ) ) { 
            matchs( "deformation", 4 );
            if ( matchs_exact("on") ) {
                shearDeformation=true;
            } else if( matchs_exact("off") ) {
                shearDeformation=false;            
            } // end if //
            
        } else if( matchs( "coordinates", 5 ) ) { 
            if (numberOfNodes>0) {
                readCoordinatesAndConstraints();
            } else {
                cerr << errorMessage[4];
                exit(0);
            } // end if 
        } else if( matchs( "materials", 4 ) ) { 
            if (numberOfMaterials>0) {
                readMaterials();
            } else {
                cerr << errorMessage[7];
                exit(0);        
            } // end if //
        } else if( matchs( "secType", 5 ) ) { 
            if (numberOfSectionTypes>0) {
                readSectionTypes(sectionTypes);
            } else {
                cerr << errorMessage[8];
                exit(0);        
            } // end if //
        } else if( matchs( "incidences", 4 ) ) {
            if (numberOfElements>0) {
                readIncidences();
            } else {
                cerr << errorMessage[6];
                exit(0);    
            } // end if //
        } else if( matchs( "elements", 4 ) ) {
            if (numberOfElements>0 and numberOfSectionTypes>0) {
                defineElements(sectionTypes);
            } else {
                cerr << errorMessage[9];
                exit(0);    
            } // end if //
        } else if( matchs_exact( "echo" ) ) { 
          // turn read echo on or off
          matchs_exact( "on" ) ? setEcho( true ) : setEcho( false );
          
        /*  
        } else if( matchs( "print", 4 ) ) {
            if( matchs( "StuctData", 6 )) {
                //printStrucData();                // Moved to setBasicData.cpp. It is executed just before defining load cases // mostly ade1b.cpp
                //assembleGlobalStifnessMatrix();  // Moved to setBasicData.cpp. It is executed just before defining load cases
            } else {
                cerr << errorMessage[11] << getLineCounter() << '\n'; 
            } // end if //
        */    
            
        } else if( matchs( "plot", 4 ) ) {
            plotStruc();             
        } else if( matchs( "loading", 5 ) ) {
        
            if (GlobalKIsNotReduce) {
                GlobalKIsNotReduce=false;
                printStrucData();
                assembleGlobalStifnessMatrix();    // mostly ade1c.cpp 
            } // end if //
        
            if (numberOfLoadCases > 0) {
                readLoadCases();
                if (areThereLoadedElements) {
                    finishLoadVector();
                } // end if //
                
                
                
                solveDisplacements();        // this is at the top of ade1f.cpp 
                printJointDisplacements();   // this follows in ade1f.cpp
                printElementsSolution();     // this follows in ade1f.cpp
                printJointsSolution();       // this finishes ade1f.cpp                
            } else {
                cerr << errorMessage[15] << '\n'; exit(1);
            } // end if //
            
        } else if( matchs( "combine", 4 ) and  matchs( "elements", 4 ) ) {
        
            combineLoadCases();
            
        } else if( endcrd() ) {
            continue; // jump out of the while loop            
        } else {
          cerr << errorMessage[11] << getLineCounter() << '\n'; // exit(0);
        } // end if
        
    } // end while //
    if (sectionTypes!=nullptr) freeMat(sectionTypes);
} // end of OpenStruc::driver() //    
