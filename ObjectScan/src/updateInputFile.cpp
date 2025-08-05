#include "ObjectScan.h"

void Scan::updateInputFile(const positiveInt &val)
{
    if (val > 0) {
        cin.rdbuf(myInputFiles[numberOfInputFilesOpened-1]->rdbuf());
        is_comming_from_file=true;
        prompt = false;
    } else {
        in_from_stdin();
    } // end if //
} // end of Scan::updateInputFile() //
