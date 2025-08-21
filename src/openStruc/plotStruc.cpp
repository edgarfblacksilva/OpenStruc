#include <iostream>

#include "openStruc.h"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

void OpenStruc::plotStruc() 
{
    auto *temp = new real[coordPerJoint];
    std::vector<double> x, y, z;
    std::map<std::string, std::string> keywords;
    keywords.insert(std::pair<std::string, std::string>("color", "red") );
    keywords.insert(std::pair<std::string, std::string>("lw", "1.25") );
    //keywords.insert(std::pair<std::string, std::string>("ls", "-.") );

    for(auto elementNber=one; elementNber<=numberOfElements; ++elementNber) {
        elm->read(elementNber-1);
        
        auto jointI=elm->getElementJointI();
        jnt->read(jointI-1);
        jnt->getCoord(temp);
        
        x.push_back(temp[0]);
        y.push_back(temp[1]);
        if( coordPerJoint == 3) {
            z.push_back(temp[2]);
        } // end if //
        
        auto jointJ=elm->getElementJointJ();
        jnt->read(jointJ-1);
        jnt->getCoord(temp);

        x.push_back(temp[0]);
        x.push_back(NAN);
        y.push_back(temp[1]);
        y.push_back(NAN);
        if( coordPerJoint == 3) {
            z.push_back(temp[2]);
            z.push_back(NAN);
        } // end if //        
    } // end for //    
    delete[] temp;
    if( coordPerJoint == 3) {
        plt::plot3(x, y, z, keywords);
        plt::set_zlabel("Z"); // set_zlabel rather than just zlabel, in accordance with the Axes3D method
    } else {
        plt::plot(x, y, keywords);    
    } // end if //

    plt::title(ProblemTitle);
    plt::xlabel("X");
    plt::ylabel("Y");
    plt::grid(true);
    plt::show();
} // end of OpenStruc::plotStruc() //
