#include "ObjectScan.h"

bool Scan::numd(double &number)
{
    if (readyToMove) {
        doScan();
    } // end if //
    if (!endcrd()) {
        char ch;
        positiveInt length;
        bool num=true;
        length =strlen(currentToken);
        ch = currentToken[0];

        if (length == 1) {
            if (isdigit(ch)) {
                number=atof(currentToken);
                readyToMove=true;
                return true;
            } else if (ch =='.') {
                number=0.0;
                readyToMove=true;
                return true;
            } // end if //
        } // end if //

        if (ch =='.' and length == 1) {
            number=0.0;
            readyToMove=true;
            return true;
        } // end if //

        if (ch == '+' or ch == '-' or ch =='.'  or isdigit(ch)) {
            bool sign=false, ex10=false, point=false;
            positiveInt i=1;
            do {
                ch = currentToken[i];
                if (isdigit(ch)) {
                    ++i;
                    continue;
                } // end if //
                if (ch =='+' or ch =='-' or ch =='.' or ch =='e') {
                    switch (ch) {
                    case 'e':
                        if (!ex10) {
                            ex10=true;
                            point=true;
                            ++i;
                        } else {
                            num=false;
                        } // end if //
                        break;
                    case '+':
                    case '-':
                        if (!sign and ex10) {
                            sign=true;
                            ++i;
                        } else {
                            num=false;
                        } // end if //
                        break;
                    case '.':
                        if (!point) {
                            point=true;
                            ++i;
                        } else {
                            num=false;
                        } // end if //
                        break;
                    } // end switch //
                } else {
                    return false;
                } // end if //
            } while (num and i<length); // end while do //
        } else {
            return false;
        } // end if //

        if (num) {
            number = atof(currentToken);
            readyToMove=true;
            return true;
        } // end if //
    } // end if //

    return false;
} // end of Scan::numd() //
