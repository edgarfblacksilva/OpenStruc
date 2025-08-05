#include "ObjectScan.h"

bool Scan::setInputFile(const char *filename)
{
    is_comming_from_file=true;
    if (numberOfInputFilesOpened < MaxInpFiles) {
        myInputFiles[numberOfInputFilesOpened] = new (fstream);
        myInputFiles[numberOfInputFilesOpened]->open(filename,ios::in);
        if (myInputFiles[numberOfInputFilesOpened]->fail() == 0) {
            ++numberOfInputFilesOpened;
            updateInputFile(numberOfInputFilesOpened);
            prompt = false;
            return true; // this mean O.K.
        } else {
            cerr << "\nObjectScan Error(1): File named \'" << filename  << "\' cannot be oppened." << endl;
        } // end if //
    } else {
        cerr << "\nObjectScan Error(2): The number of simultanusly opened input files has been reached.\n"
            "                    Increase the value of the data member: 'MaxInpFiles' in the \n"
            "                    ObjectScan system and recompile.";
    } // end if //
    return false;
} // end of Scan::setInputFile() //
