#include <vector>
using std::vector;

#include "openStruc.h"
#define square(x) ((x)*(x))

void OpenStruc::getPrimaryForcesDueToLoads()
{
    if (lineNumber > 56) {
        header();
        cout << titleCase[loadCase] << "\n\n";
        lineNumber+=2;
        elm->printElementInfo(1);lineNumber+=2;
    } else {
        elm->printElementInfo(1);lineNumber+=2;        
    } // end if //

    do {
        readLine();    
    } while ( endcrd() ); // end do-while //

    int intlst[100],errCode; // variables used by the trlist() method
    intPos listSize;
    int iplist {1}; // variables used to test trxlst() method
    int iVal;
    
    vector <real> wX, wY, wZ, aW, bW;                       // uniform
    vector <intPos> kW;                                     // k factor for uniform
    
    vector <real> cX, cY, cZ, aC;                           // concentrated
    vector <intPos> kC;                                     // k factor for concentrated
    
    vector <intPos> kLV;                                    // k factor for linear variable
    vector <real> wXi, wYi, wZi, wXj, wYj, wZj, aWv, bWv;   // linear variable
    
    vector <intPos> kCC;                                    // k factor for couple
    vector <real> copX, copY, copZ, aCop;                   // couple
    
    vector <real> torX, aTor, bTor;                         // torsion    

    do {  // this do-while begins reading a list of elements
        trlist(intlst,sizeof(intlst)/sizeof(int),numberOfElements,listSize,errCode);
        if (errCode == 4) {
            //cerr << errorMessage[21] <<  getLineCounter() <<'\n';
            break;
        } // end if //
        double val;
        real ato1 {0.0}, dty {0.0}, dtz {0.0}, by {0.0},bz {0.0};
        do {   // this do-while read the temperature gradients if any 
            if(matchs_exact( "dtx")  ) {
                if (numd(val)) {                    
                    if ( structureType !=  grid) {
                        ato1 = static_cast<real>(val);
                    } else {
                        cerr << errorMessage[20] <<  getLineCounter() <<'\n'; exit(20);
                    } // end if //                
                } else {
                    cerr << errorMessage[13] <<  getLineCounter() <<'\n'; exit(13);
                } // end if //
            } else if(matchs_exact( "dty")  ) {
                if (numd(val)) {                    
                    if ( structureType ==  twoDFrame or structureType ==  threeDFrame) {
                        dty = static_cast<real>(val);
                    } else {
                        cerr << errorMessage[20] <<  getLineCounter() <<'\n'; exit(20);
                    } // end if //                
                } else {
                    cerr << errorMessage[13] <<  getLineCounter() <<'\n'; exit(13);
                } // end if //
            } else if(matchs_exact( "dtz")  ) {
                if (numd(val)) {                    
                    if ( structureType ==  grid or structureType ==  threeDFrame) {
                        dtz = static_cast<real>(val);
                    } else {
                        cerr << errorMessage[20] <<  getLineCounter() <<'\n'; exit(20);
                    } // end if //                
                } else {
                    cerr << errorMessage[13] <<  getLineCounter() <<'\n'; exit(13);
                } // end if //
            // by and bz are only needed if there is an temperature gradient AND the section type is arbitrary                
            } else if(matchs_exact( "by")  ) {
                if (numd(val)) {                    
                    by = static_cast<real>(val);
                } else {
                    cerr << errorMessage[13] <<  getLineCounter() <<'\n'; exit(13);
                } // end if //
            } else if(matchs_exact( "bz")  ) {
                if (numd(val)) {                    
                    bz = static_cast<real>(val);
                } else {
                    cerr << errorMessage[13] <<  getLineCounter() <<'\n'; exit(13);
                } // end if //
            } // end if //
        } while ( !endcrd() ); // end do-while this ends reading the temperature gradients if any //

        do { // this do-while read lines until a non-empty line
            readLine();    
        } while ( endcrd() ); // end do-while //
        
        intPos nUL  {zero};
        intPos nCL  {zero};
        intPos nLVL {zero};
        intPos nCCL {zero};
        intPos nTOR {zero};
        do { // this do-while begins reading the types of loads        
            if ( matchs( "uniform", 3)  ) { // this is the uniform load case
                if ( matchs( "local", 4)  ) {
                    kW.push_back(zero);
                } else if ( matchs( "global", 4) ) {
                    kW.push_back(one);
                } else if ( matchs( "projected", 4) ) {
                    kW.push_back(2);
                } else {
                    cerr << errorMessage[17] <<  getLineCounter() <<'\n'; exit(17);            
                } // end if //
                wX.push_back(0.0);
                wY.push_back(0.0);
                wZ.push_back(0.0);
                aW.push_back(0.0);
                bW.push_back(0.0);
                
                do {  // this do-while read the uniform loads 
                    if( matchs_exact( "wx") ) {
                        if ( structureType !=  grid) {
                            if (numd(val)) {
                                wX[nUL] = static_cast<real>(val);
                            } // end if //                        
                        } else {
                            cerr << errorMessage[18] <<  getLineCounter() <<'\n'; exit(18);
                        } // end if //
                    } else if(matchs_exact( "wy")  ) {
                        if ( structureType !=  grid) {
                            if (numd(val)) {
                                wY[nUL] = static_cast<real>(val);
                                //wy = static_cast<real>(val);
                            } // end if //                        
                        } else {
                            cerr << errorMessage[18] <<  getLineCounter() <<'\n'; exit(18);
                        } // end if //
                    } else if(matchs_exact( "wz")  ) {
                        if ( structureType !=  twoDTruss and structureType !=  twoDFrame) {
                            if (numd(val)) {
                                wZ[nUL] = static_cast<real>(val);
                                //wz = static_cast<real>(val);
                            } // end if //
                        } else {
                            cerr << errorMessage[18] <<  getLineCounter() <<'\n'; exit(18);
                        } // end if //
                    } else if(matchs_exact( "la")  ) {
                        if (numd(val)) {
                            aW[nUL] = static_cast<real>(val);
                            //la = static_cast<real>(val);
                        } else {
                            cerr << errorMessage[13] <<  getLineCounter() <<'\n'; exit(13);
                        } // end if //
                    } else if(matchs_exact( "lb")  ) {                    
                        if (numd(val)) {
                            bW[nUL] = static_cast<real>(val);
                            //lb = static_cast<real>(val);
                        } else {
                            cerr << errorMessage[13] <<  getLineCounter() <<'\n'; exit(13);
                        } // end if //
                    // by and bz are only needed if there is an temperature gradient AND the section type is arbitrary                
                    //} else {
                        //doScan();   
                    } // end if //
                } while ( !endcrd() ); // end do-while //
                ++nUL;
                
            } else if ( matchs( "concentrated", 4) ) {            
                if ( matchs( "local", 4)  ) {
                    kC.push_back(zero);
                } else if ( matchs( "global", 4) ) {
                    kC.push_back(one);
                } else {
                    cerr << errorMessage[17] <<  getLineCounter() <<'\n'; exit(17);            
                } // end if //
                
                cX.push_back(0.0);
                cY.push_back(0.0);
                cZ.push_back(0.0);
                aC.push_back(0.0);
                
                do {  // this do-while read the concentrated loads 
                    if( matchs_exact( "px") ) {
                        if ( structureType !=  grid) {
                            if (numd(val)) {
                                cX[nCL] = static_cast<real>(val);
                            } // end if //                        
                        } else {
                            cerr << errorMessage[18] <<  getLineCounter() <<'\n'; exit(18);
                        } // end if //
                    } else if(matchs_exact( "py")  ) {
                        if ( structureType !=  grid) {
                            if (numd(val)) {
                                cY[nCL] = static_cast<real>(val);
                                //wy = static_cast<real>(val);
                            } // end if //                        
                        } else {
                            cerr << errorMessage[18] <<  getLineCounter() <<'\n'; exit(18);
                        } // end if //
                    } else if(matchs_exact( "pz")  ) {
                        if ( structureType !=  twoDTruss and structureType !=  twoDFrame) {
                            if (numd(val)) {
                                cZ[nCL] = static_cast<real>(val);
                                //wz = static_cast<real>(val);
                            } // end if //
                        } else {
                            cerr << errorMessage[18] <<  getLineCounter() <<'\n'; exit(18);
                        } // end if //
                    } else if(matchs_exact( "la")  ) {
                        if (numd(val)) {
                            aC[nCL] = static_cast<real>(val);
                            //la = static_cast<real>(val);
                        } else {
                            cerr << errorMessage[13] <<  getLineCounter() <<'\n'; exit(13);
                        } // end if //
                    //} else {
                        //doScan();   
                    } // end if //
                } while ( !endcrd() ); // end do-while //
                ++nCL;                                
                
            } else if ( matchs( "linear", 3) ) {        
                if ( matchs( "local", 4)  ) {
                    kLV.push_back(zero);
                } else if ( matchs( "global", 4) ) {
                    kLV.push_back(one);
                } else if ( matchs( "projected", 4) ) {
                    kLV.push_back(2);
                } else {
                    cerr << errorMessage[17] <<  getLineCounter() <<'\n'; exit(17);            
                } // end if //

                wXi.push_back(0.0); wXj.push_back(0.0);
                wYi.push_back(0.0); wYj.push_back(0.0);
                wZi.push_back(0.0); wZj.push_back(0.0);
                aWv.push_back(0.0);
                bWv.push_back(0.0);

                do {  // this do-while read the linear variable loads 
                    if( matchs_exact( "wxi") ) {
                        if ( structureType !=  grid) {
                            if (numd(val)) {
                                wXi[nLVL] = static_cast<real>(val);
                            } // end if //                        
                        } else {
                            cerr << errorMessage[18] <<  getLineCounter() <<'\n'; exit(18);
                        } // end if //
                    } else if(matchs_exact( "wyi")  ) {
                        if ( structureType !=  grid) {
                            if (numd(val)) {
                                wYi[nLVL] = static_cast<real>(val);
                            } // end if //                        
                        } else {
                            cerr << errorMessage[18] <<  getLineCounter() <<'\n'; exit(18);
                        } // end if //
                    } else if(matchs_exact( "wzi")  ) {
                        if ( structureType !=  twoDTruss and structureType !=  twoDFrame) {
                            if (numd(val)) {
                                wZi[nLVL] = static_cast<real>(val);
                            } // end if //
                        } else {
                            cerr << errorMessage[18] <<  getLineCounter() <<'\n'; exit(18);
                        } // end if //

                    } else if(matchs_exact( "wxj")  ) {
                        if ( structureType !=  grid) {
                            if (numd(val)) {
                                wXj[nLVL] = static_cast<real>(val);
                            } // end if //                        
                        } else {
                            cerr << errorMessage[18] <<  getLineCounter() <<'\n'; exit(18);
                        } // end if //
                        
                    } else if(matchs_exact( "wyj")  ) {
                        if ( structureType !=  grid) {
                            if (numd(val)) {
                                wYj[nLVL] = static_cast<real>(val);
                            } // end if //                        
                        } else {
                            cerr << errorMessage[18] <<  getLineCounter() <<'\n'; exit(18);
                        } // end if //
                        
                    } else if(matchs_exact( "wzj")  ) {
                        if ( structureType !=  twoDTruss and structureType !=  twoDFrame) {
                            if (numd(val)) {
                                wZj[nLVL] = static_cast<real>(val);
                            } // end if //
                        } else {
                            cerr << errorMessage[18] <<  getLineCounter() <<'\n'; exit(18);
                        } // end if //
                        
                    } else if(matchs_exact( "la")  ) {
                        if (numd(val)) {
                            aWv[nLVL] = static_cast<real>(val);
                        } else {
                            cerr << errorMessage[13] <<  getLineCounter() <<'\n'; exit(13);
                        } // end if //
                    } else if(matchs_exact( "lb")  ) {                    
                        if (numd(val)) {
                            bWv[nLVL] = static_cast<real>(val);
                            //lb = static_cast<real>(val);
                        } else {
                            cerr << errorMessage[13] <<  getLineCounter() <<'\n'; exit(13);
                        } // end if //
                    } // end if //
                } while ( !endcrd() ); // end do-while //
                ++nLVL;
                
            } else if ( matchs( "couple", 4) ) {
                if ( matchs( "local", 4)  ) {
                    kCC.push_back(zero);
                } else if ( matchs( "global", 4) ) {
                    kCC.push_back(one);
                } else {
                    cerr << errorMessage[17] <<  getLineCounter() <<'\n'; exit(17);            
                } // end if //
                copX.push_back(0.0);
                copY.push_back(0.0);
                copZ.push_back(0.0);
                aCop.push_back(0.0);

                do {  // this do-while read the concentrated couple loads 
                    if( matchs_exact( "mx") ) {
                        if ( structureType !=  twoDFrame and structureType !=  twoDTruss and structureType !=  threeDTruss) {
                            if (numd(val)) {
                                copX[nCCL] = static_cast<real>(val);
                            } // end if //                        
                        } else {
                            cerr << errorMessage[18] <<  getLineCounter() <<'\n'; exit(18);
                        } // end if //
                    } else if(matchs_exact( "my")  ) {
                        if ( structureType !=  twoDFrame) {
                            if (numd(val)) {
                                copY[nCCL] = static_cast<real>(val);
                                //wy = static_cast<real>(val);
                            } // end if //                        
                        } else {
                            cerr << errorMessage[18] <<  getLineCounter() <<'\n'; exit(18);
                        } // end if //
                    } else if(matchs_exact( "mz")  ) {
                        if ( structureType !=  grid) {
                            if (numd(val)) {
                                copZ[nCCL] = static_cast<real>(val);
                                //wz = static_cast<real>(val);
                            } // end if //
                        } else {
                            cerr << errorMessage[18] <<  getLineCounter() <<'\n'; exit(18);
                        } // end if //
                    } else if(matchs_exact( "la")  ) {
                        if (numd(val)) {
                            aCop[nCCL] = static_cast<real>(val);
                            //la = static_cast<real>(val);
                        } else {
                            cerr << errorMessage[13] <<  getLineCounter() <<'\n'; exit(13);
                        } // end if //
                    //} else {
                        //doScan();   
                    } // end if //
                } while ( !endcrd() ); // end do-while //
                ++nCCL;                                
                
            } else if ( matchs( "torsion", 3) ) {
                torX.push_back(0.0);
                aTor.push_back(0.0);
                bTor.push_back(0.0);
                
                do {  // this do-while read the concentrated loads 
                    if( matchs_exact( "tx") ) {                    
                        if (numd(val)) {
                            torX[nTOR] = static_cast<real>(val);
                        } // end if //                        
                    } else if(matchs_exact( "la")  ) {
                        if (numd(val)) {
                            aTor[nTOR] = static_cast<real>(val);
                            //la = static_cast<real>(val);
                        } else {
                            cerr << errorMessage[13] <<  getLineCounter() <<'\n'; exit(13);
                        } // end if //
                    } else if(matchs_exact( "lb")  ) {
                        if (numd(val)) {
                            bTor[nTOR] = static_cast<real>(val);
                            //la = static_cast<real>(val);
                        } else {
                            cerr << errorMessage[13] <<  getLineCounter() <<'\n'; exit(13);
                        } // end if //
                    } // end if //
                } while ( !endcrd() ); // end do-while //
                ++nTOR;                                
            } else {
                break;    
            } // end if //
            do {
                readLine();    
            } while ( endcrd() ); // end do-while //            
        } while ( true ); // this do-while  ends reading the types of loads
        
///////////////////////////////////////////////////////////////////////////////////////////////////////////

        //  Creating an auxiliary vector
        real *d=nullptr;
        dimVec(d,dofPerElement);
        real axiso, vyisoi, vzisoi, pariso,  vyisoj,vzisoj;
        //  end of Creating an auxiliary vector

        iplist=1;
        do { // this do-while begins processing a load type for all element of this list
            trxlst(iVal, iplist, intlst,listSize);
            if (lineNumber > 56) {
                header();
                cout << titleCase[loadCase] << "\n\n";
                lineNumber+=2;
                elm->printElementInfo(1);lineNumber+=2;
            } // end if //
            cout << '\n'; ++lineNumber;

            memset(&d[1], 0, dofPerElement*sizeof(real));
            
            //elm->clearForcesInElement();
            auto elementRecNber = static_cast<intPos>(iVal-1);
            
            
            #if defined (ENGLISH)
            cout << "    Element" << setw(6) <<  iVal
                << "         DTX =" << setw(9) << setprecision(3) << ato1
                << " DTY ="  << setw(8) << setprecision(3) << dty
                << " DTZ ="  << setw(8) << setprecision(3) << dtz << '\n';
            #elif defined (ESPANOL)
            cout << "    Miembro" << setw(6) <<  iVal
                << "        ATO1 =" << setw(9) << setprecision(3) << ato1
                << " DTY="  << setw(9) << setprecision(3) << dty
                << " DTZ="   << setw(9) << setprecision(3) << dtz << '\n';
            #endif  
            ++lineNumber;
            elm->read(elementRecNber);
            auto length=elm->getLength();

            if (by == 0) {
                by =  elm->getBy();
            } // end if //
            if (bz == 0) {
                bz =  elm->getBz();
            } // end if //

            axiso  = 0.0;
            vyisoi = 0.0;
            vyisoj = 0.0;
            pariso = 0.0;
            vzisoi = 0.0;
            vzisoj = 0.0;

            auto elementForcesRecNber=zero;             
            if (numberOfElementCombinations > 0) {
                elementForcesRecNber = numberOfLoadCases * elementRecNber + loadCase -1;
            } else {
                elementForcesRecNber=elementRecNber;
            } // end if //
            elm->readEF(elementForcesRecNber);

            // Calculo de las fuerzas primarias debido a cargas uniformes  // check results using https://calcresource.com/statics-fixed-beam.html
            for(auto l = zero; l < nUL; ++l) { // Solo se ejecuta si existen cargas uniformes
                auto wx = wX[l];
                auto wy = wY[l];
                auto wz = wZ[l];
                auto a = aW[l];
                auto b = bW[l];
                auto &k = kW[l];
                
                if (aW[l] < 0.0) {
                    a = -(aW[l]*length);
                } // end if //
                
                if (bW[l] < 0.0) {
                    b = -(bW[l]*length);
                } else if (bW[l] == 0.0){
                    b = length - a;
                } // end if //
                
                if ( k > 0) {
                    auto Wx1 = wx;
                    auto Wy1 = wy;
                    auto Wz1 = wz;
                    
                    if ( k == 2) {
                        auto *coordI = new real[3]();
                        auto *coordJ = new real[3]();

                        auto jointRecNber = elm->getElementJointI() - 1;
                        jnt->read(jointRecNber);
                        jnt->getCoord(coordI);

                             jointRecNber = elm->getElementJointJ() - 1;
                        jnt->read(jointRecNber);
                        jnt->getCoord(coordJ);
                        
                        Wx1 = wx * sqrt( square( coordJ[1] - coordI[1]) + square(coordJ[2]-coordI[2])) / length;
                        Wy1 = wy * sqrt( square( coordJ[0] - coordI[0]) + square(coordJ[2]-coordI[2])) / length;
                        Wz1 = wz * sqrt( square( coordJ[0] - coordI[0]) + square(coordJ[1]-coordI[1])) / length;
                        delete[] coordJ;
                        delete[] coordI;
                    } // end if //
                    real r[9];
                    elm->getElementRotations(r);                    
                    wx = r[0] * Wx1 + r[1] * Wy1 +  r[2] * Wz1;
                    wy = r[3] * Wx1 + r[4] * Wy1 +  r[5] * Wz1;
                    wz = r[6] * Wx1 + r[7] * Wy1 +  r[8] * Wz1;
                    
                } // end if //
                cout << "    Npu = " << setw(1) << l+1
                    << " Wx ="  << setw(9) << setprecision(3) << wx
                    << " Wy ="   << setw(9)                   << wy
                    << " Wz ="   << setw(9)                   << wz
                    << " La  ="   << setw(9)                   << a
                    << " Lb  ="   << setw(9)                   << b << '\n';
                ++lineNumber;
                elm->applyUniformLoads(d,axiso,vyisoi,vyisoj,vzisoi,vzisoj, wx,wy,wz,a,b);
            } // end for l nUL//
            
            // Calculo de las fuerzas primarias debido a cargas concentradas  // check results using https://calcresource.com/statics-fixed-beam.html
            for(auto l = zero; l< nCL; ++l) { // Solo se ejecuta si existen cargas concentradas
                auto cx = cX[l];
                auto cy = cY[l];
                auto cz = cZ[l];
                auto a = aC[l]; 
                auto &k = kC[l];
            
                if (aC[l] < 0.0) {
                    a = -(aC[l]*length);
                } // end if //
        
                if ( k > 0) {
                    real Cx1,Cy1,Cz1;
                    Cx1 = cx;
                    Cy1 = cy;
                    Cz1 = cz;
                    
                    real r[9];
                    elm->getElementRotations(r);                    
                    
                    cx = r[0] * Cx1 + r[1] * Cy1 +  r[2] * Cz1;
                    cy = r[3] * Cx1 + r[4] * Cy1 +  r[5] * Cz1;
                    cz = r[6] * Cx1 + r[7] * Cy1 +  r[8] * Cz1;
                } // end if //
                
                cout << "    Npc = " << setw(1) << l+1
                    << " Px =" << setw(9) << setprecision(3) << cx
                    << " Py =" << setw(9)                    << cy
                    << " Pz =" << setw(9)                    << cz
                    << " La  =" << setw(9)                    << a << '\n';
                ++lineNumber;
                elm->applyConcentratedLoads(d,axiso,vyisoi,vyisoj,vzisoi,vzisoj, cx,cy,cz,a);                
            } // end for l nCL //
            
            // Calculo de las fuerzas primarias debido a cargas linealmente variables  // check results using https://calcresource.com/statics-fixed-beam.html
            for(auto l = zero; l< nLVL; ++l) { // Solo se ejecuta si existen linealmente variables
                
                auto Wx = wXi[l];
                auto Px = wXj[l];
                auto Wy = wYi[l];
                auto Py = wYj[l];
                auto Wz = wZi[l];
                auto Pz = wZj[l];
                auto a  = aWv[l];
                auto b  = bWv[l];
                auto k  = kLV[l];

                if (aWv[l] < 0.0) {
                    a = -(aWv[l]*length);
                } // end if //
                if (bWv[l] < 0.0) {
                    b = -(bWv[l]*length);
                } else if (bWv[l] == 0.0){
                    b = length-a;
                } // end if //

                if ( k > 0) {

                    auto Wxi = Wx;
                    auto Wyi = Wy;
                    auto Wzi = Wz;

                    auto Wxj = Px;
                    auto Wyj = Py;
                    auto Wzj = Pz;
                        
                    if ( k == 2) {
                        auto *coordI = new real[3]();
                        auto *coordJ = new real[3]();

                        auto jointRecNber = elm->getElementJointI() - 1;
                        jnt->read(jointRecNber);
                        jnt->getCoord(coordI);

                             jointRecNber = elm->getElementJointJ() - 1;
                        jnt->read(jointRecNber);
                        jnt->getCoord(coordJ);
                        
                        real temp = sqrt( square( coordJ[1] - coordI[1]) + square(coordJ[2]-coordI[2])); 
                        Wxi = Wx * temp / length;
                        Wxj = Px * temp / length;
                        
                              temp = sqrt( square( coordJ[0] - coordI[0]) + square(coordJ[2]-coordI[2]));
                        Wyi = Wy * temp / length;
                        Wyj = Py * temp / length;

                              temp = sqrt( square( coordJ[0] - coordI[0]) + square(coordJ[1]-coordI[1]));
                        Wzi = Wz * temp / length;
                        Wzj = Pz * temp / length;
             
                        delete[] coordJ;
                        delete[] coordI;
                    } // end if //
                    real r[9];
                    elm->getElementRotations(r);                    
                    Wx = r[0] * Wxi + r[1] * Wyi +  r[2] * Wzi;
                    Wy = r[3] * Wxi + r[4] * Wyi +  r[5] * Wzi;
                    Wz = r[6] * Wxi + r[7] * Wyi +  r[8] * Wzi;


                    Px = r[0] * Wxj + r[1] * Wyj +  r[2] * Wzj;
                    Py = r[3] * Wxj + r[4] * Wyj +  r[5] * Wzj;
                    Pz = r[6] * Wxj + r[7] * Wyj +  r[8] * Wzj;
                } // end if //

                cout << "    Npv = "  << setw(1) << l+1
                    << " Wxi=" << setw(9) << setprecision(3) << Wx
                    << " Wxj="  << setw(9)                    << Px
                    << " Wyi="  << setw(9)                    << Wy
                    << " Wyj="  << setw(9)                    << Py
                    << " Wzi="  << setw(9)                    << Wz
                    << " Wzj="  << setw(9)                    << Pz
                    << " La  ="   << setw(9)                    << a
                    << " Lb  ="   << setw(9)                    << b << '\n';
                
                ++lineNumber;
                elm->applyLinVarLoads(d,axiso,vyisoi,vyisoj,vzisoi,vzisoj, Wx,Px,Wy,Py,Wz,Pz,a,b);
            } // end for l nLVL//

            // Calculo de las fuerzas primarias debido a Momento concentrados
            for(auto l = zero; l< nCCL; ++l) { // Solo se ejecuta si existen Momentos concentrados
                auto Px = copX[l];
                auto Py = copY[l];
                auto Pz = copZ[l];
                auto a = aCop[l]; 
                auto &k = kCC[l];
            
                if (aCop[l] < 0.0) {
                    a = -(aCop[l]*length);
                } // end if //

                if ( k > 0) {
                    real r[9];
                    elm->getElementRotations(r);                    
                    real Px1,Py1,Pz1;
                    Px1 = Px;
                    Py1 = Py;
                    Pz1 = Pz;
                    Px = r[0] * Px1 + r[1] * Py1 +  r[2] * Pz1;
                    Py = r[3] * Px1 + r[4] * Py1 +  r[5] * Pz1;
                    Pz = r[6] * Px1 + r[7] * Py1 +  r[8] * Pz1;
                } // end if //
                
                cout << "    Npar= " << setw(1) << l+1
                    << " Mx =" << setw(9) << setprecision(3) << Px
                    << " My =" << setw(9)                    << Py
                    << " Mz =" << setw(9)                    << Pz
                    << " La  =" << setw(9)                    << a << '\n';
                ++lineNumber;
                elm->applyConcentratedMoment(d,pariso,vyisoi,vyisoj,vzisoi,vzisoj, Px,Py,Pz,a);                
            } // end for l npar//
            
            // Calculo de las fuerzas primarias debido a Torsor concentrado
            for(auto l = zero; l< nTOR; ++l) { // Solo se ejecuta si existen Torsor concentrado        
                auto Tx = torX[l];
                auto a = aTor[l];
                auto b = bTor[l];

                if (aTor[l] < 0.0) {
                    a = -(aTor[l]*length);
                } // end if //
                
                if (bTor[l] < 0.0) {
                    b = -(bTor[l]*length);
                } else if (bTor[l] == 0.0){
                    b = length - a;
                } // end if //

                cout << "    Ntor= " << setw(1) << l+1
                    << "   T =" << setw(9) << setprecision(3) << Tx
                    << " La  ="  << setw(9)                    << a
                    << " Lb  ="  << setw(9)                    << b << '\n';
                ++lineNumber;
                elm->applyUniformTorsion(d,pariso, Tx,a,b );
            } // end for l ntor//
            
            elm->applyTempGradients(d, ct[elm->getMatType()], ato1, dty, dtz, by ,bz);
            elm->finishApplingPrimaryForces(d,length,axiso,pariso,vyisoi,vyisoj,vzisoi,vzisoj); 
            elm->setForcesInElement(static_cast<real>(true),0);
            elm->writeEF(elementForcesRecNber);
                
        } while(iplist != 0); // end do-while(). this do-while ends processing a load type for all elements of this list
        cout << '\n';
        ++lineNumber;

        freeVec(d);
        torX.clear(); aTor.clear(); bTor.clear();
        copX.clear(); copY.clear(); copZ.clear(); aCop.clear();kCC.clear();
        wXi.clear(); wYi.clear(); wZi.clear(); wXj.clear(); wYj.clear(); wZj.clear(); aWv.clear(); bWv.clear(); kLV.clear();        
        cX.clear(); cY.clear(); cZ.clear(); aC.clear();  kC.clear();
        wX.clear();wY.clear();wZ.clear();aW.clear();bW.clear();kW.clear();
    } while (true);  // this do-while ends reading a list of elements

    areThereLoadedElements=true;
} // end of OpenStruc::getPrimaryForcesDueToLoads() //
