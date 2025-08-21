#include <iomanip>
using std::setw;
using std::setprecision;

#include "threeDFrameElement.h"

void ThreeDFrameElement::printElementPrimaryForces(const intPos &elementRecNber, intPos &lin)
{
    cout << setw(11) << elementRecNber+1
         << setw(7) << jointI << setw(14) << setprecision(3) 
         << -forcesInElement[1] << setw(13) 
         <<  forcesInElement[2] << setw(13) 
         <<  forcesInElement[3] << setw(13) 
         << -forcesInElement[4] << setw(13) 
         <<  forcesInElement[5] << setw(13) 
         << -forcesInElement[6] << '\n';
    cout << setw(18) <<  jointJ << setw(14) 
         <<  forcesInElement[7]  << setw(13) 
         << -forcesInElement[8]  << setw(13) 
         << -forcesInElement[9]  << setw(13) 
         <<  forcesInElement[10] << setw(13) 
         << -forcesInElement[11] << setw(13) 
         <<  forcesInElement[12] << '\n';
    lin+=2;
} // end of ThreeDFrameElement::printElementPrimaryForces()  //
