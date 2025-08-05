#include "openStruc.h"
void OpenStruc::combineLoadCases()
{
    //  Local Variables
    auto  **factor            = (real **)   new real*   [numberOfElementCombinations];
    auto **loadCase           = (intPos **) new intPos* [numberOfElementCombinations];
    auto *numberOfCombination = (intPos *)  new intPos  [numberOfElementCombinations];
    
    real *conv=nullptr;
    auto ncomb=zero;
    //  End of local variables
    
    // defining the size of the record for file elementsForcesBinaryFile
    elm->clearForcesInElement();
    // end of defining the size of the record for file elementsForcesBinaryFile

    header();
    
    if( isstring() ) {
        positiveInt nchar; 
        char text[120];
        scan_contents( text, nchar );
        titleHip[0]= text;
    } // end if //
    
    cout << "\n    ";  
    cout << titleHip[0];    
    #if defined (ENGLISH)
    cout << "\n    Hypothesis   Load Case    Factor\n";
    #elif defined (ESPANOL)
    cout << "\n    Hipotesis  Caso de Carga  Factor\n";
    #endif      
    lineNumber+=3;

    for(auto i=zero; i<numberOfElementCombinations; ++i) {
        do {
            readLine();        // this jumps empty lines
        } while ( endcrd() ); // end do-while //
    
        matchs_exact("cases");
        matchs_exact("to");
        matchs("combine",4);
        int iVal;
        if (integr(iVal)) {
            ncomb = static_cast<intPos>(iVal);
        
            
            numberOfCombination[i] = ncomb;
            loadCase[i] = new intPos[ncomb];
            factor[i]= new real[ncomb];
            
            cout << setw(13) << i+1;
            for(auto j=zero;j<ncomb; ++j) {
                do {
                    readLine();        // this jumps empty lines
                } while ( endcrd() ); // end do-while //

                if (integr(iVal)) {
                    loadCase[i][j] = static_cast<intPos>(iVal);
                    double val;
                    if (numd(val)) {
                        factor[i][j] = static_cast<real>(val);
                    } else {
                        cerr <<  errorMessage[13]  << getLineCounter() << '\n'; exit(13); 
                    } // end if //
                } else {
                    cerr <<  errorMessage[12]  << getLineCounter() << '\n'; exit(12); 
                } // end if //
                
                
                if (j==0) {
                    cout << setw(13);
                } else {
                    cout << setw(26);
                } // end if //
                cout << loadCase[i][j]  << setw(14) << setprecision(3) << factor[i][j] << '\n';
                ++lineNumber;
            } // end for //
            cout << '\n';
            ++lineNumber;
        } else {
            cerr <<  errorMessage[12]  << getLineCounter() << '\n'; exit(0); 
        } // end if //
    } // end for //
    
    
    header();
    elm->printElementInfo(4); lineNumber+=2;    
    elm->printElementInfo(5); lineNumber+=1;

    auto totalNumberOfForces=elm->getTotalNumberOfForces();
    conv = new real[numberOfElementCombinations * totalNumberOfForces];
    for(auto elementRecNber=zero; elementRecNber<numberOfElements; ++elementRecNber ) {
        memset(conv, 0, (numberOfElementCombinations*totalNumberOfForces)*sizeof(real));
        auto elementForcesRecNber=elementRecNber*numberOfLoadCases;
        
        for(auto j=zero; j<numberOfElementCombinations; ++j) {
                
            for(auto k=zero; k<numberOfCombination[j] ; ++k) {
                //cout << "    elementForcesRecNber: " << (elementForcesRecNber + loadCase[j][k]) << '\n';
                
                elm->readEF( elementForcesRecNber+loadCase[j][k]-1 );
            
                for(auto i=zero; i<dofPerJoint; ++i) {
                    conv[j*totalNumberOfForces+i] +=  elm->getForcesInElement(i+1)*factor[j][k];
                    //conv[j][i] += forcesInElement[i+1]*factor[j][k];
                } // end for //
                
                for(auto i=dofPerJoint, ii=2*dofPerJoint+one; i<totalNumberOfForces-dofPerJoint; ++i, ++ii) {
                    conv[j*totalNumberOfForces+i] += elm->getForcesInElement(ii)*factor[j][k];
                    //conv[j][i] += forcesInElement[ii]*factor[j][k];
                } // end for //
                
                for(auto i=totalNumberOfForces-dofPerJoint, ii=dofPerJoint+one; i<totalNumberOfForces; ++i,++ii) {
                    conv[j*totalNumberOfForces+i] += elm->getForcesInElement(ii)*factor[j][k];
                    //conv[j][i] += forcesInElement[ii]*factor[j][k];
                } // end for //
            } // end for //
        } // end for //
            

        if (elm->getSecctionsInsideAnElement()>0 and lineNumber > 56 - (elm->getSecctionsInsideAnElement()+2)*numberOfElementCombinations) {
            header();
            elm->printElementInfo(5);  lineNumber+=1;
        } else if (elm->getSecctionsInsideAnElement() == 0 and lineNumber > (56 -2*numberOfElementCombinations)){
            header();
            elm->printElementInfo(5);  lineNumber+=1;
        } // end if //


        elm->read(elementRecNber);
        real segment = elm->getLength() /(elm->getSecctionsInsideAnElement()  +1);
        
        real position = 0.0;
        cout << setw(15) <<  elementRecNber+1 << setprecision(3);
        
        
        for(auto jj=zero; jj<elm->getSecctionsInsideAnElement()+2; ++jj) {
            if (jj==zero) {
                cout  << setw(8) << position;
            } else {
                cout  << setw(23)  << position;
            } // end if
            position += segment;
            
            for(auto j=zero; j<numberOfElementCombinations; ++j) {
                if (j==0) {
                    cout << setw(10) << j+1;
                } else {
                    cout << setw(33) << j+1;
                } // end if
                for(auto i = jj*dofPerJoint; i<(jj+1)*dofPerJoint; ++i) {
                    cout << setw(12) << conv[j*totalNumberOfForces+i];
                    //cout << setw(12) << conv[j][i];
                } // end for //
                cout << '\n';
            } // end for //
            
        } // end for //
        lineNumber+=(elm->getSecctionsInsideAnElement()+2)*numberOfElementCombinations;
    } // end for //
    delete[]conv;
    
    header();
    if (numberOfNodeCombinations == 0) { // take numberOfNodeCombinations = numberOfElementCombinations;
        numberOfNodeCombinations=numberOfElementCombinations;    
        #if   defined ENGLISH
        titleHip[1]="    Using the same combinations of the elements";
        #elif defined (ESPANOL)
        titleHip[1]="    Usando las mismas combinaciones de los miembros";    
        #endif  
        
        cout << '\n';
        cout << titleHip[1];
        #if   defined ENGLISH
        cout << "\n    Hypothesis   Load Case    Factor\n";
        #elif defined ESPANOL
        cout << "\n    Hipotesis  Caso de Carga  Factor\n";
        #endif  
        lineNumber+=3;
        for(auto i=zero; i<numberOfNodeCombinations; ++i) {
            cout << setw(13) << i+1;
            for(auto j=zero;j<numberOfCombination[i]; ++j) {
                if (j==0) {
                    cout << setw(13);
                } else {
                    cout << setw(26);
                } // end if //
                cout << loadCase[i][j]  << setw(14) << setprecision(3) << factor[i][j] << '\n';
                ++lineNumber;
            } // end for //
            cout << '\n';
            ++lineNumber;
        } // end for //
    } else {
       for(auto i=zero; i<numberOfElementCombinations; ++i) {
            delete loadCase[i]; 
            delete factor[i]; 
       } // end for //
       delete [] loadCase;
       delete [] factor;
       delete [] numberOfCombination;

       factor = (real **) new real* [numberOfNodeCombinations];
       loadCase = (intPos **) new intPos* [numberOfNodeCombinations];
       numberOfCombination=new intPos[numberOfNodeCombinations];
       
       
        do {
            readLine();        // this jumps empty lines
        } while ( endcrd() ); // end do-while //
        matchs( "combine", 4 ); matchs( "nodes", 4 );
       
        if( isstring() ) {
            positiveInt nchars; 
            char text[120];
            scan_contents( text, nchars );
            titleHip[1]= text;
        } // end if //

        cout << "\n    ";
        cout << titleHip[1];
        #if   defined ENGLISH
        cout << "\n    Hypothesis   Load Case    Factor\n";
        #elif defined ESPANOL
        cout << "\n    Hipotesis  Caso de Carga  Factor\n";
        #endif  
        lineNumber+=3;


        
        for(auto i=zero; i<numberOfNodeCombinations; ++i) {
            do {
                readLine();        // this jumps empty lines
            } while ( endcrd() ); // end do-while //
        
            matchs_exact("cases");
            matchs_exact("to");
            matchs("combine",4);
            int iVal;
            if (integr(iVal)) {
                ncomb = static_cast<intPos>(iVal);
                
                numberOfCombination[i] = ncomb;
                loadCase[i] = new intPos[ncomb];
                factor[i]= new real[ncomb];
                
                cout << setw(13) << i+1;
                for(auto j=zero;j<numberOfCombination[i]; ++j) {
                    
                    do {
                        readLine();        // this jumps empty lines
                    } while ( endcrd() ); // end do-while //

                    if (integr(iVal)) {
                        loadCase[i][j] = static_cast<intPos>(iVal);
                        double val;
                        if (numd(val)) {
                            factor[i][j] = static_cast<real>(val);
                        } else {
                            cerr <<  errorMessage[13]  << getLineCounter() << '\n'; exit(13); 
                        } // end if //
                    } else {
                        cerr <<  errorMessage[12]  << getLineCounter() << '\n'; exit(12); 
                    } // end if //
                    
                    if (j==0) {
                        cout << setw(13);
                    } else {
                        cout << setw(26);
                    } // end if //
                    cout << loadCase[i][j]  << setw(14) << setprecision(3) <<factor[i][j] << '\n';
                    ++lineNumber;
                } // end for //
                cout << '\n';
                ++lineNumber;
                
            } else {
                cerr <<  errorMessage[12]  << getLineCounter() << '\n'; exit(0); 
            } // end if //
        } // end for //
        
    } // end if //
    header();
    jnt->printJointInfo(5);lineNumber+=3;
    conv = new real [numberOfNodeCombinations*dofPerJoint];

    for(auto jointRecNber=zero; jointRecNber<numberOfNodes; ++jointRecNber) {
        memset(conv, 0, (numberOfNodeCombinations*dofPerJoint)*sizeof(real));
        auto jointReactionRecNber = jointRecNber*numberOfLoadCases;

        for(auto j=zero; j<numberOfNodeCombinations; ++j) {
            for(auto k=zero; k<numberOfCombination[j] ; ++k) {
                //cerr << "position: " << jointReactionRecNber << "   ";
                
                jnt->readReac(jointReactionRecNber + loadCase[j][k]-1);
                for(auto i=zero; i<dofPerJoint; ++i) {
                    conv[j*dofPerJoint+i] += jnt->getJointReactionsRecord(i)*factor[j][k];
                } // end for //
            } // end for //
        } // end for //
        
        if (lineNumber > (56 -numberOfNodeCombinations)) {
            header();
            jnt->printJointInfo(5);lineNumber+=3;
        } // end if //
        cout << setw(13) << jointRecNber+1;
        for(auto j=zero; j<numberOfNodeCombinations; ++j) {
            if (j==0) {
                cout << setw(6) << j+1;
            } else {
                cout << setw(19) << j+1;
            } // end if //
            for(auto k=zero; k<dofPerJoint; ++k) {
                cout << setw(12) << setprecision(3) << conv[j*dofPerJoint+k];
            } // end for //
            cout << '\n';
        } // end for //
        ++lineNumber;
    } // end for //
    delete [] conv;

   for(auto i=zero; i<numberOfNodeCombinations; ++i) {
        delete loadCase[i]; 
        delete factor[i]; 
   } // end for //
   delete [] loadCase;
   delete [] factor;
   delete [] numberOfCombination;    
} // end of OpenStruc::combineLoadCases() //
