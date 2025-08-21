#include "openStruc.h"

void OpenStruc::getTitle()
{
    char *text = new char [LINEWITH];
    intPos nchar; 

    readLine();
    
    if (matchs("Structure", 4) ) {
        doScan();
        while (!endcrd()) {
            scan_contents( text, nchar );
            ProblemTitle +=  text;
            ProblemTitle +=  " ";
            doScan();
        } // end while //
        //cout << "    Problem Title: " <<  ProblemTitle << '\n'; 
    }  else  {
        cout << "    The input file must start with the command 'Structure ' followed by a title\n"; 
        exit(-1);
    } // end if //
    delete [] text;
} // end of getTitle()

