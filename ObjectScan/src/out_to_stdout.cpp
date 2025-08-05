#include "ObjectScan.h"

void Scan::out_to_stdout()
{
    myOutputFile.close();
    cout.rdbuf(myStdOut);
} // end of Scan::out_to_stdout() //
