#include<cmath>
#include "threeDFrameElement.h"

void ThreeDFrameElement::defineSectionProperties(real *__restrict const myData, const intPos &secType, const intPos &matType, const real &e, const real &g ) 
{
    real shearAreaFactorY=0.0;
    real shearAreaFactorZ=0.0;
    // calculating element section properties  
    switch (secType) {
        case 1: // rectangular section
            real c,d,f;
            real b,h;
            b = myData[0];
            h = myData[1];
            myData[4]= b; // bz is b
            myData[5]= h; // by is h
            myData[0]= b*h; // factor[0]; //area
            myData[2]=myData[3]=myData[0]/12;
            myData[2] *= (b*b);
            myData[3] *= (h*h);
            if (b < h) {
                c = b;
                d = h;
            } else {
                c = h;
                d = b;
            } // end if //
            f = c / d;
            myData[1] = c*c*c * d * (1 - .63 * f + .0525 * f*f*f*f*f) / 3;
            shearAreaFactorY = shearAreaFactorZ = 6.0/5.0;
            break;
        case 2: // circular section
            real radio;
            radio = myData[0]*0.5;
            myData[4] = myData[5] = myData[0]; // bz is d and // by is d            

            myData[0]= static_cast<real>(M_PI)*radio*radio;
            myData[1] = 0.5*myData[0]*radio*radio;
            myData[2] = myData[3] = 0.5*myData[1];            
            shearAreaFactorY = shearAreaFactorZ = 10./9.0;
            break;
        case 3: //arbritary section...
            shearAreaFactorY = 1.5;
            shearAreaFactorZ = 1.5;
        default:
            break;
    } // end switch //

    myData[6] =  shearAreaFactorY * e * myData[2] / (g*myData[0]);
    myData[7] =  shearAreaFactorZ * e * myData[3] / (g*myData[0]);
    
    myData[0] *= e;
    myData[1] *= g;
    myData[2] *= e;
    myData[3] *= e;
    myData[8] = static_cast<real>(matType);
    // end of setting element properties    
} // end of ThreeDFrameElement::defineSectionProperties() //
