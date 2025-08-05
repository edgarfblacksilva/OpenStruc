#include "ObjectScan.h"

void Scan::trlist(int *list, const positiveInt &listSize, const int &iall, positiveInt &nlist, int &errCode )
{
    char *where;
    bool nextNeg= false;

    if (readyToMove) {
        doScan();
    } // end if //

    errCode=1;
    if (matchs_exact( "all")) {
        list[0] = 1;
        list[1] = -iall;
        list[2] = 1;
        nlist = 3;
        return ;
    } // end if //

    nlist = 0;
    while (!endcrd()) {
        if (nlist > listSize) {
            --nlist;
            errCode = 3;
            return;
        } // end if //

        if ( matchs_exact("to") or  matchs_exact("-")  ) {
            if (nextNeg==false) {
                if (nlist > 0) {
                    nextNeg = true;
                    continue;
                } else {
                    errCode = 4;
                    return;
                } // end if //
            } else {
                errCode = 2;
                return;
            } // end if //
        } // end if //

        if (currentToken != NULL) {
            if (( where = strchr(currentToken, '-') ) ) {
                if ( nextNeg == false) {
                    nextNeg = true;
                    *where = '\0';
                    if (strlen(currentToken) > 0) {
                        if (integr( list[nlist] )   ) {
                            ++nlist;
                        } else {
                            errCode=4;
                            return;
                        }  // end if //
                    } // end if //
                    currentToken = ++where;
                    if (( where = strchr(currentToken, '-') )) {
                        errCode = 2;
                        return;
                    } else if (strlen(currentToken) > 0) {
                        readyToMove=false;
                        continue;
                    } // end if //
                } else {
                    // doble negative
                    errCode = 2;
                    return;
                } // end if //
            } // end if //

            if (strlen(currentToken) == 1 and currentToken[0] == '+') {
                return;
            } // end if //

            if (( where = strchr(currentToken, '+') ) ) {
                *where = '\0';
                if (strlen(currentToken) > 0) {
                    if (integr( list[nlist] )   ) {
                        ++nlist;
                    } else {
                        errCode=4;
                        return;
                    }  // end if //
                } // end if //
                currentToken = ++where;
                if (strlen(currentToken) > 0) {
                    readyToMove=false;
                    continue;
                } else {
                    return;
                } // end if //
            } // end if //
        } // end if //

        if (integr( list[nlist] )) {  // is an integer
            ++nlist;
            if (nextNeg ) {
                list[nlist-1] *=-1;
                nextNeg = false;
                if ( matchs_exact("by") ) {
                    if (integr(list[nlist])) {
                        nlist++;
                    } else {
                        errCode = 2;
                        list[nlist] = 1;
                        return;
                    } // end if //
                } else {
                    if (nlist > 1)  {
                        list[nlist++] = 1;
                    } // end if //
                } // end if //
            } //end if //
            continue;
        } else { // not a integer
            if (nlist == 0) {
                errCode = 4;
            } else if (nextNeg or matchs_exact("by")) {
                errCode = 2;
            } else {
                break;
            } // end if //
            return;
        } // end if //
    } // end while //

    if(nlist == 0) {
        errCode = 4;
        //   } else if (list[0] < 0 ) {
        //       errCode = 5;
    } else {
        // cheking for consistensy of the list
        if (list[0] < 0 ) {    // first number must be positive
            errCode = 5;
        } // end if //
        int limit = nlist-1;
        int k = 1;
        int temp;
        bool mustBePos=false;

        while (k < limit) {
            if (list[k] < 0 ) {
                if (mustBePos) {
                    errCode = 5;
                    break;
                } else {
                    temp = -(list[k] + list[k-1]) * list[k+1];
                    if (temp < 0) {
                        errCode = 5;
                        break;
                    } // end if //
                    ++k;
                    mustBePos = true;
                }  // end if //
            } else {
                mustBePos=false;
            } // end if //
            ++k;
        } // end while //
    } // end if //

    return;
} // end of Scan::trlist() //
