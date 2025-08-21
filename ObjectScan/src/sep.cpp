#include "ObjectScan.h"

bool Scan::sep(positiveInt &septyp)
{
    const char separray[] = {"![~-(+|&]<*);^\\/{%}>?:#@`="};
/*
i: 0  !
i: 1  [
i: 2  ~          <<<----------
i: 3  -
i: 4  (
i: 5  +
i: 6  |
i: 7  &
i: 8  ]
i: 9  <          <<<----------
i: 10  *
i: 11  )
i: 12  ;
i: 13  ^
i: 14  \          <<<----------
i: 15  /
i: 16  {          <<<----------
i: 17  %
i: 18  }          <<<----------
i: 19  >
i: 20  ?
i: 21  :
i: 22  #
i: 23  @
i: 24  `          <<<----------
i: 25  =
*/
    if (readyToMove) {
        doScan();
    } // end if //
    if (!endcrd() and strchr(separray,currentToken[0]) != NULL) {
        septyp = strcspn(separray, currentToken);
        
        // this switch is just to reproduce the output produced by the old SCAN
        // I believe this switch can be safely removed.
        switch (septyp) {
        case 2:
        case 9:
        case 14:
        case 16:
        case 18:
        case 24:
            septyp = 0;
            break;
        } // end of switch //
        //  end of switch this switch is just to reproduce the output produced by the old SCAN        
        readyToMove=true;
    } // end if //
    return readyToMove;
} // end of Scan::sep(positiveInt &septyp) //
