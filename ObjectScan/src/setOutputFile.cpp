#include "ObjectScan.h"

bool Scan::setOutputFile(const char *myfilename)
{
    OutFileName = myfilename;
    if (myOutputFile.is_open()) {
        myOutputFile.close();
    } // end if //
    
    myOutputFile.open(myfilename,ios::out|ios::app);

    bool result=false;
    if (myOutputFile.is_open()) {
        cout.rdbuf(myOutputFile.rdbuf());
        result = true;
    } // end if //
    return result;
} // Scan::setOutputFile() 
