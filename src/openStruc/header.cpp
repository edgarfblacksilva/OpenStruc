#include "openStruc.h"

void OpenStruc::header()
{ 
    auto t = time(nullptr);
    auto tm = *localtime(&t);

    cout << fixed;
    cout << "\f\n";
    cout <<  headerMessage[0] << setw(3) << ++pageNumber << '\n';
    cout <<  headerMessage[1];
    cout <<  headerMessage[2] <<  setprecision(2) << getOpenStrucVersion() << headerMessage[3];
    cout <<  headerMessage[4];
    cout <<  headerMessage[5];
    cout <<  headerMessage[1];

    //cout.fill('0');
    cout << ProblemTitle
         << "    " << headerMessage[6] 
#if defined (ENGLISH)
         << std::put_time(&tm, "%m-%d-%Y")
#elif defined (ESPANOL)
         << std::put_time(&tm, "%d-%m-%Y")
#endif    
         << "    " << headerMessage[7] 
         << std::put_time(&tm, "%H:%M:%S")
         << '\n';
    lineNumber=9;
} // end of function OpenStruc::header() //


void OpenStruc::setHeaderMessages()
{ 
    headerMessage = new string[8];

#if defined (ENGLISH)
    headerMessage[0] = "                                                                           Page";
    headerMessage[1] = "*************************************************************************\n";
    headerMessage[2] = "* OpenStruc - Version ";
    headerMessage[3] = "                                              *\n";
    headerMessage[4] = "* A program for the Static Analysis of Structures                       *\n";
    headerMessage[5] = "* Programer: E.F.B.S.                                                   *\n";
    headerMessage[6] = "  Date: ";
    headerMessage[7] = "  Time: ";
#elif defined (ESPANOL)
    headerMessage[0] = "                                                                         Pagina";
    headerMessage[1] = "*************************************************************************\n";
    headerMessage[2] = "* OpenStruc - Versión ";
    headerMessage[3] = "                                              *\n";
    headerMessage[4] = "* Un Programa para el Análisis Estático de Estructuras                  *\n";
    headerMessage[5] = "* Programador: E.F.B.S.                                                 *\n";
    headerMessage[6] = "  Fecha: ";
    headerMessage[7] = "  Hora: ";
#endif    
} // end of function OpenStruc::setHeaderMessages() //
