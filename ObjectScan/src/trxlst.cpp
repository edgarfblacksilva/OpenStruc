#include "ObjectScan.h"

void Scan::trxlst(int &next, int &iplist, int *list, const positiveInt &nlist  )
{
    static int *expandedList;
    static int expandedSize;


    if (iplist == 1) {      // creating the exanded list
        if (nlist > 1) {
            expandedSize = sizlst(list,nlist);
            //         if ((expandedList) !=NULL) {
            //             delete [] (expandedList);
            //         } // end if //
            expandedList = new int [expandedSize];
            --expandedList;
            positiveInt  i = 0;
            int  expanded_i = 1;
            int increment, endValue;

            while (i < nlist) {
                if (list[i] > 0) {
                    expandedList[expanded_i++] = list [i++];
                } else {
                    endValue = -list[i++];
                    increment = list[i++];
                    if (increment > 0) {
                        for (int temp = expandedList[expanded_i-1]+increment;    temp <= endValue ; temp = expandedList[expanded_i++]+increment) {
                            expandedList[expanded_i] = temp;
                        } // end for //
                    } else {
                        for (int temp = expandedList[expanded_i-1]+increment;    temp >= endValue ; temp = expandedList[expanded_i++]+increment) {
                            expandedList[expanded_i] = temp;
                        } // end for //
                    } // end if //
                } // end if //
            } // end while //
            next = expandedList[iplist];
            ++iplist;
        } else {
            next = list[0];
            iplist = 0;
        } // end if //
    } else if (iplist <= expandedSize) {
        next = expandedList[iplist++];
        if (iplist > expandedSize) {
            ++expandedList;
            delete [] expandedList;
            iplist = 0;
        } // end if //
    } else {
        ++expandedList;
        delete [] expandedList;
        iplist = 0;
    } // end if //
} // end of Scan::trxlst() //
