#include <iostream>
using std::to_string;

#include "gnuplot-iostream.h"
#include "openStruc.h"

void OpenStruc::plotStruc() 
{
/*
    string version = "        ";
    sprintf(&version[0], "%.2f",getOpenStrucVersion() );
    string ProgramVersion= "set title 'OpenScan -- Version " + version +  "'\n";  
*/
	std::vector<boost::tuple<double, double, double, string> > pts_A;

	Gnuplot gp;
	
	//gp << "set terminal png\n";
	//gp << "set output 'logo.png'";
	
    gp << "set title '" +  ProblemTitle + "'\n";

    gp << "set grid xtics ytics ztics\n";
    gp << "set xlabel 'X'\n";
    gp << "set ylabel 'Y'\n";
    if (coordPerJoint==3) gp << "set zlabel 'Z'\n";
    
    gp << "set style line 1  linewidth 1.5 pointsize 1.0  pointtype 7 linecolor rgb '#ff0000'\n";    
	//gp << "set xrange [-10:10]\nset yrange [-10:10]\nset zrange [-10:10]\n";

    auto *temp = new real[coordPerJoint];
    //dimVec(temp,coordPerJoint);
        
    for(auto elementNber=one; elementNber<=numberOfElements; ++elementNber) {
        elm->read(elementNber-1);
        auto jointI=elm->getElementJointI();
        
        jnt->read(jointI-1);
        jnt->getCoord(temp);

        if( coordPerJoint == 3) {
            pts_A.push_back(boost::make_tuple(temp[0],temp[1],temp[2]," "));        
        } else {
            pts_A.push_back(boost::make_tuple(temp[0],temp[1],0," "));        
        } // end if //
        
        auto jointJ=elm->getElementJointJ();

        jnt->read(jointJ-1);
        jnt->getCoord(temp);

        if( coordPerJoint == 3) {
            pts_A.push_back(boost::make_tuple(temp[0],temp[1],temp[2],"\n\n"));        
        } else {
            pts_A.push_back(boost::make_tuple(temp[0],temp[1],0,"\n\n"));        
        } // end if //        
    } // end for //      
    //freeVec(temp);
    delete[] temp;


	// Data will be sent via a temporary file.  These are erased when you call
	// gp.clearTmpfiles() or when gp goes out of scope.  If you pass a filename
	// (e.g. "gp.file1d(pts, 'mydata.dat')"), then the named file will be created
	// and won't be deleted (this is useful when creating a script).
	
	
    if( coordPerJoint == 3) {
        gp << "splot" 
           << gp.file1d(pts_A) << "title '' with linespoints ls 1\n";
    } else {
        gp << "plot" 
           << gp.file1d(pts_A) << "title '' with linespoints ls 1\n";
    } // end if //
    
    
} // end of OpenStruc::plotStruc() //
