#include "openStruc.h"

int main (int argc, char *argv[]) 
{
    clock_t start;
    
    OpenStruc structure;

    switch (argc) {
    case (2):
    case (3):
        if (!structure.setInputFile(argv[1])) {
            cerr << "Input data file '" << argv[1] << "' not found\n";
            exit(-1);
        } // endif //
        if (argc == 2) {
            structure.setWorkingFileName(argv[1]);
            //structure.setOutputFileNames();
        } else if (argc == 3) {
            if (structure.setOutputFile(argv[2])) {    // setOutputFile() == true means file was opened
                //structure.setOutputFileNames();
            } else {
                cerr << ".... Specified file cannot be opened.... \n"
                    << "....command ignored....\n";
                        
            } // endif //
        } // endif //
        break;
    } // endswitch //
    
    start = clock();
    
    structure.driver();
    
    cout << fixed << setprecision(2)
        << "Running Time: " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC
        <<  "  sec. \n";
    
    return 0;
} // end of main() //
