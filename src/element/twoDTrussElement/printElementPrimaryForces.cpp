#include <iomanip>
using std::setw;
using std::setprecision;

#include "twoDTrussElement.h"

void TwoDTrussElement::printElementPrimaryForces(const intPos &elementRecNber, intPos &lin)
{
    cout << setw(11) << elementRecNber+1
         << setw(7) << jointI << setw(14) << setprecision(3) 
         << -forcesInElement[1] << setw(13) 
         <<  forcesInElement[2] << '\n';
    cout << setw(18) <<  jointJ << setw(14) 
         <<  forcesInElement[3]  << setw(13) 
         << -forcesInElement[4]  << '\n';
    lin+=2;
} // end of ThreeDTrussElement::printElementPrimaryForces()  //
