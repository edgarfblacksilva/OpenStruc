#include "ObjectScan.h"

void Scan::in_from_stdin()
{
    is_comming_from_file=false;
    prompt = true;
    cin.rdbuf(myStdIn);
} // end of Scan::in_from_stdin() //
