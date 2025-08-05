#include "openStruc.h"

void OpenStruc::printStrucData() 
{
    auto *message= new string[8];

#if defined (ENGLISH)
    message[0] = "    Number of Nodes: ";
    message[1] = "    Number of Elements:";
    message[2] = "    Number of Materials:";
    message[3] = "    Propeties of the meterials types";
    message[4] = "    Type            E             G             Ct          Weight";
    message[5] = "\n    Volumen: ";
    message[6] = "Structure Total Weight:";
    message[7] = "Mean BandWidth: ";
#elif defined (ESPANOL)
    message[0] = "    Numero de Juntas: ";
    message[1] = "    Numero de Elementos:";
    message[2] = "    Numero de Materiales:";
    message[3] = "    Propiedades de los materiales usados";
    message[4] = "    Tipo            E             G             Ct            Peso";
    message[5] = "\n    Volumen: ";
    message[6] = "Peso total de la Estructura:";
    message[7] = "BandWidth Promedio: ";

#endif    

    header();
    cout << setprecision(4) << scientific 
         << message[0] << setw(9) << numberOfNodes    << '\n'  
         << message[1] << setw(7) << numberOfElements  << '\n'  
         << message[2] << setw(6) << numberOfMaterials << "\n\n"  
         << message[3] << '\n'
         << message[4] << '\n'; 

    for(auto i=one; i<=numberOfMaterials; ++i){
        cout << setw(8) << i << setw(13) << e[i] << setw(14) << g[i] << setw(15) << ct[i] << setw(16) << weight[i] << '\n';
    } // end for //
    cout << '\n';

    lineNumber += (numberOfMaterials+7);
    if (lineNumber+numberOfNodes > 56){
        header();
    } // end if //       
    
    jnt->printJointInfo(0);lineNumber+=2;

    intPos size = (dofPerJoint >= coordPerJoint ?   dofPerJoint: coordPerJoint);
    real *temp=nullptr;    
    dimVec(temp,size);

    for(auto jointNber=zero; jointNber<numberOfNodes; ++jointNber) {
        if (lineNumber > 56) {
            header();
            jnt->printJointInfo(0);lineNumber+=2;
        } // end if //
        jnt->read(jointNber);
        
        
        cout << fixed;
        cout << setw(11) << jointNber+1;
        

        jnt->getCoord(&temp[1]);
        cout << setprecision(3);
        for (auto i=one; i<=coordPerJoint; ++i) {
            cout << setw(10) << temp[i];
        } // end for //
        
        for (auto i=zero; i<dofPerJoint; ++i) {
            cout << setw(4) << (constraint[jointNber][i] ? 'T':'F' );
        } // end for //                
        
        cout << ' ' << setprecision(4) << scientific;
        jnt->getSpringConstants(&temp[1]);         
        for (auto i=one; i<=dofPerJoint; ++i) {
            cout << setw(11) << temp[i];
        } // end for //
        cout << '\n';
        ++lineNumber;
    } // end for //
    freeVec(temp);
    cout << '\n';
    ++lineNumber;


    real vol=0;
    real totalWeight= 0.0;
    real length; 
    auto matType=zero;
    auto *stiffnessData = new real [7];
    //dimVec(stiffnessData,7);

    if (lineNumber+numberOfElements > 56) {
        header();
    } // end if //         
    
    elm->printElementInfo(0); lineNumber+=2;
    for(auto elementNber=one; elementNber<=numberOfElements; ++elementNber) {
        if (lineNumber > 56) {
            header();
            elm->printElementInfo(0);lineNumber+=2;
        } // end if //
        elm->read(elementNber-1);
        
        elm->getElementStiffnessFactors(stiffnessData);
        length=elm->getLength();
        matType=elm->getMatType();
        
        real lengthOverE = length / e[matType];
        real ar = elm->getAr() * lengthOverE;
        real Ix = elm->getIx() * length/g[matType];        
        real Iy = elm->getIy() * lengthOverE;
        real Iz = elm->getIz() * lengthOverE;
        
        vol += length*ar;
        totalWeight += weight[matType]*length*ar;
        cout << fixed << "    "
            << setw(5) << elementNber
            << setw(10) << elm->getElementJointI()
            << setw(8) << elm->getElementJointJ() << setprecision(2)
            << setw(11) << length << uppercase << scientific  << setprecision(3)
            << setw(11) << ar
            << setw(10) << Ix
            << setw(11) << Iy
            << setw(11) << Iz << fixed << setprecision(2)
            << setw(7) << stiffnessData[4]
            << setw(7) << stiffnessData[5]
            << setw(7) << stiffnessData[6]
            << setw(6) << stiffnessData[0]
            << setw(7) << stiffnessData[1]
            << setw(7) << stiffnessData[2]
            << setw(7) << stiffnessData[3]
            << setw(7) << matType; 
            
        //if(elm->getBz() > 0) {
        //    cout << setw(10) << elm->getBz() << setw(7) << elm->getBy() << '\n'; 
        //} else {
        //    cout << '\n';   
        //} // end if //   
        
        cout << '\n';
        ++lineNumber;
    } // end for //      

    real meanBW=0.0;
    // Calculo de la media-banda promedio
    for (auto i = one; i <= numberOfEqations; ++i) {
        meanBW += (i-leftCol[i]);
    } // endfor //
    meanBW += numberOfEqations;
    meanBW /= numberOfEqations;
    // end of Calculo de la media-banda promedio

    cout << setprecision (3) << message[5] << setw(6) << vol << setw(40) << message[6] << setw(10) << totalWeight <<  setw(40) << message[7] << meanBW << "\n\n";
    lineNumber += 3;
    delete[] stiffnessData;
    delete [] message;  
} // end of OpenStruc::printStrucData() //
