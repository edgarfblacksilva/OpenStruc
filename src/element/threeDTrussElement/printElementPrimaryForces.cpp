#include <iomanip>
using std::setprecision;
using std::setw;

#include "threeDTrussElement.h"

void ThreeDTrussElement::printElementPrimaryForces(const intPos &elementRecNber, intPos &lin)
{
    cout << setw(11) << elementRecNber+1
         << setw(7) << jointI << setw(14) << setprecision(3) 
         << -forcesInElement[1] << setw(13) 
         <<  forcesInElement[2] << setw(13) 
         <<  forcesInElement[3] << '\n';
    cout << setw(18) <<  jointJ << setw(14) 
         <<  forcesInElement[4] << setw(13) 
         << -forcesInElement[5] << setw(13) 
         << -forcesInElement[6] << '\n';
    lin+=2;
} // end of ThreeDTrussElement::printElementPrimaryForces()  //
