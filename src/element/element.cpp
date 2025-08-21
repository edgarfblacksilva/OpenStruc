#include <filesystem>
using std::filesystem::remove;

#include "element.h"

fstream Element::elementsBinaryFile;
fstream Element::elementsForcesBinaryFile;
intPos  Element::sizeOfElementRecord;
intPos  Element::sizeOfElementForcesRecord;
intPos  Element::totalNumberOfForces;
intPos  Element::secctionsInsideAnElement {0}; // 0 is the default value; it is defined early in driver.cpp; 
string  Element::fileName1;
string  Element::fileName2;
string  Element::elementMessages [];
real *__restrict Element::forcesInElement=nullptr;
real Element::globalTempIncrement {0.0};
bool Element::gridTypeElement=false;

Element::Element(const string &fileName) 
{
    fileName1 = fileName + ".elm";
    fileName2 = fileName + ".efs";

    elementsBinaryFile.open(fileName1.c_str(),  ios::in | ios::out | ios::trunc | ios::binary);
    if (!elementsBinaryFile) {
        cerr << "File " <<  fileName1 << " could not be opened.\n";
        exit(1);
    } // end if //
    
    elementsForcesBinaryFile.open(fileName2.c_str(), ios::in|ios::out| ios::trunc|ios::binary);
    if (!elementsForcesBinaryFile) {
        cerr << "File " << fileName2 << " could not be opened.\n";
        exit(1);
    } // end if //
} // end of Element constructor //

Element::~Element()
{
    elementsBinaryFile.close();
    elementsForcesBinaryFile.close();
    remove(fileName1);
    remove(fileName2);
    delete [] forcesInElement;
} // end of Element destructor //
void Element::write(const intPos &rec) {  
    elementsBinaryFile.seekp(sizeOfElementRecord*rec,ios::beg);
    elementsBinaryFile.write(reinterpret_cast<const char *> (this), sizeOfElementRecord);        
} // end of Element::write() //

void Element::read(const intPos &rec) {
    elementsBinaryFile.seekg(sizeOfElementRecord*rec,ios::beg);
    elementsBinaryFile.read (reinterpret_cast< char *> (this), sizeOfElementRecord);        
} // end of Element::read() //

void Element::writeEF(const intPos &rec) {  
    elementsForcesBinaryFile.seekp(sizeOfElementForcesRecord*rec,ios::beg);
    elementsForcesBinaryFile.write(reinterpret_cast<const char *>(this->forcesInElement), sizeOfElementForcesRecord);        
} // end of Element::write() //

void Element::readEF(const intPos &rec) {
    elementsForcesBinaryFile.seekg(sizeOfElementForcesRecord*rec,ios::beg);
    elementsForcesBinaryFile.read (reinterpret_cast< char *> (this->forcesInElement), sizeOfElementForcesRecord);        
} // end of Element::read() //

/*
void Element::printElementInfo(const intPos &val, intPos &ln) {
       cout << elementMessages[val];
       //ln += 2;
} // end of Element::printElementInfo() //
*/

