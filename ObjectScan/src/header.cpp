#include "openStruc.h"

void OpenStruc::header()
{ 

    struct tm *current;
    time_t now;
    time(&now);
    current=localtime(&now);

    cout << fixed;
    cout << "\f\n";
    cout <<  headerMessage[0] << setw(10) << ++pageNumber << '\n';
    cout <<  headerMessage[1];
    cout <<  headerMessage[2] <<  setprecision(2) << getOpenStrucVersion() << headerMessage[3];
    cout <<  headerMessage[4];
    cout <<  headerMessage[5];
    cout <<  headerMessage[1];

    cout.fill('0');
    cout << ProblemTitle
        << '\t' << headerMessage[6] << setw(2) << current->tm_mon+1 
        << '-' << setw(2) << current->tm_mday 
        << '-' << setw(4)<< current->tm_year+1900
        << '\t' << headerMessage[7] << setw(2) << current->tm_hour 
        << ':' << setw(2) << current->tm_min 
        << ':' << setw(2) << current->tm_sec << "\n\n";
    cout.fill(' ');
    lineNumber=9;
} // end of function OpenStruc::header() //
