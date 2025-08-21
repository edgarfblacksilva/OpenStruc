#include "openStruc.h"

void OpenStruc::formLeftColumn(const intPos &ji, const intPos &jj) 
{
    intPos *gdof=nullptr;    
    dimVec(gdof,dofPerElement);

    //       Calculo de leftColumn
    for (auto k=one; k <= dofPerJoint; ++k) {
        if (constraint[ji-1][k-1] == true) {
            gdof[k] = 0;    
        } else {
            gdof[k] = (ji-1)*dofPerJoint + k;        
        } // end if //
    } // endfor //

    for (auto k=dofPerJoint+1; k <= dofPerElement; ++k) {
        if (constraint[jj-1][k-dofPerJoint-1] == true) {
            gdof[k] = 0;      
        } else {
            gdof[k]= (jj-2)*dofPerJoint + k;
        } // end if //
    } // endfor //

    intPos row, col;
    for (auto k=one; k <= dofPerElement; ++k) {
        if(gdof[k] > 0) {
            for (auto l=k+1; l <= dofPerElement; ++l) {
                if(gdof[l] > 0) {
                    if ( gdof[k] > gdof[l]  ) {
                        row = gdof[k];
                        col = gdof[l];
                    } else {
                        row = gdof[l];
                        col = gdof[k];
                    } // endif //
                    if ( col < leftCol[row] ) {
                        leftCol[row]= col;
                    } // endif //
                } // endif //
            } // endfor //
        } // end if //
    } // endfor //
    //  End of Calculo de leftColumn  
    freeVec(gdof);  
} // end of OpenTruss::formLeftColumn() //
