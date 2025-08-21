#include "threeDFrameElement.h"

void ThreeDFrameElement::setSectionProperties(real *myData)
{
    // seting element section properties    
    for (auto i=zero; i<4; ++i) {
        properties[i] = myData[i]/length;
    } // end for //
    for (auto i=one*4; i<6; ++i) {
        properties[i] = myData[i];
    } // end for //
    materialType=static_cast<intPos>(myData[8]);
} // end of Element::setSectionProperties() //
