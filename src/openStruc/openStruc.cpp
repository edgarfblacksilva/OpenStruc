#include "openStruc.h"

OpenStruc::OpenStruc() :    Scan(LINEWITH,MAXTK,"#",true,4), 
                            pageNumber{0}, 
                            lineNumber{1}
{
    setErrorMassages();  // this function is defines in theheader file.
    setHeaderMessages();
    titleHip  = new string [2]; // one for elements and one for reactions

} // end of OpenStruc constructor //

OpenStruc::~OpenStruc()
{
    delete j2dt;
    delete j3dt;
    delete jg;
    delete j2df;
    delete j3df;

    delete e2dt;
    delete e3dt;
    delete eg;
    delete e2df;
    delete e3df;

    delete [] errorMessage;
    delete [] headerMessage;

    delete [] titleHip;

    if (loadVector != nullptr) freeVec(loadVector);
    if (leftCol != nullptr)    freeVec(leftCol);
    if (weight != nullptr)     freeVec(weight);
    if (ct != nullptr)         freeVec(ct);
    if (g != nullptr)          freeVec(g);
    if (e != nullptr)          freeVec(e);
    if (constraint != nullptr) freeMat(constraint,0,0);
    if (structureStiffnessMatrix!=nullptr) freeMat(structureStiffnessMatrix);
    if (titleCase != nullptr) freeVec(titleCase);
    //cerr << "check in destructor what else need to be destoryed\n";
    
    
} // end of OpenStruc destructor //
