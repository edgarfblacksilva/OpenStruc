#include "ObjectScan.h"

bool Scan::readLine()
{
   char *line;
   
    while (true) {
        if (prompt) {
            if (numberOfInputFilesOpened > 0) {
                clog << setw(2) << numberOfInputFilesOpened << " > " << flush;
            } else {
                clog << "> " << flush;
            } // end if //
        } // end if //
        cin.getline(Scan::line,LineWith); ++LineCounter;
        
        positiveInt j = 0;
        while (isspace(Scan::line[j])) { // eliminating the spaces at the begining of Scan::line
           ++j;
        } // end while //
        line =  &Scan::line[j];
        
        if (!cin.eof()) {
            positiveInt lengthOfLine = strlen(line);

            if (echoLine == true and lengthOfLine > 0) {
                cout << '\t' << line << endl;
            } // end if //

            // if you  do not want a single c or C letter to be a comentary, comment the following if statement
//            if ((line[0] == 'c' or line[0] == 'C') and  (isspace(line[1]) or line[1] == '\0' )) {
//              continue;
//            } // end if //

            if (strchr(line,eolChar[0]) != NULL) {
                positiveInt i = strcspn(line, eolChar);
                lengthOfLine = i;
                if (i==0) {
                   continue;
                } else {   
                   line[i] = '\0';
                } // end if //
            } // end if //

            for (positiveInt i=0;i < lengthOfLine;++i ) {
                if (isspace(line[i]) ) {
                    line[i] = ' ';
                } // end if //
            } // end for //
            
            // line = toLowerStr(line);
            bool subCharFg = false;
            char subChar = static_cast<char>(1);     // ascii char 1 fo fill inside a string
            if (strchr(line,'"') != NULL  or strchr(line,'\'') != NULL or strchr(line,',') != NULL  ) {
                for (positiveInt i=0;i < lengthOfLine;++i ) {
                    if (line[i] == separator[0] and subCharFg) {
                        line[i] = subChar;
                    } else if (line[i] == ',' and !subCharFg) {
                        line[i] = separator[0];
                    } // end if //
                    if (line[i] == '"' or line[i] == '\'') {
                        if (subCharFg) {
                            subCharFg = false;
                        } else {
                            subCharFg = true;
                        } // end if //
                    } // end if //
                } // end for //
                subCharFg = true;
            } // end if //
            tokenIndex=0;
            token[tokenIndex] = strtok(line, separator);
            if ( token[tokenIndex] != NULL) {
                currentToken = token[tokenIndex];
            } else {
                currentToken = separator;
            } // end if //
            while (token[tokenIndex] != NULL) {
                token[++tokenIndex] = strtok(NULL, separator);
            } // end while //
            if (subCharFg) {
                for (positiveInt i=0;i<lengthOfLine;++i ) {
                    if (line[i] == subChar) {
                        line[i] = separator[0];
                    } // end if //
                } // end for //
            } // end if //
            tokenPerLine=tokenIndex;
            tokenIndex=0;
            readyToMove=false;
            return true;
        } else {
            if (numberOfInputFilesOpened > 0) {
                if (is_comming_from_file) {
                    --numberOfInputFilesOpened;
                    myInputFiles[numberOfInputFilesOpened]->close();
                    delete myInputFiles[numberOfInputFilesOpened];
                } // end if //
                updateInputFile(numberOfInputFilesOpened);
                continue;
            } else {
                //cout << "EOF"<< endl;
                return false;
            } // end if //
        } // end if //
    } // end while //
} // end of Scan::readLine() //
