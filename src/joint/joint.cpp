#include "joint.h"
#include <filesystem>
using std::filesystem::remove;
#include <cstdlib>

string Joint::fileName1;
string Joint::fileName2;
fstream Joint::jointsBinaryFile;
fstream Joint::reactionsBinaryFile;
intPos Joint::sizeOfJointRecord;
intPos Joint::sizeOfJointReactionsRecord;
string Joint::jointMessages [];
real *__restrict Joint::jointReactionsRecord=nullptr;

Joint::Joint(const string &fileName )
{
    fileName1 = fileName + ".jnt";
    fileName2 = fileName + ".rfs";
    
    jointsBinaryFile.open(fileName1.c_str(),  ios::in | ios::out | ios::trunc | ios::binary);
    if (!jointsBinaryFile) {
      cerr << "File " <<  fileName1 << " could not be opened.\n";
      exit(1);
    } // end if //
    
    reactionsBinaryFile.open(fileName2.c_str(),  ios::in | ios::out | ios::trunc | ios::binary);
    if (!reactionsBinaryFile) {
        cerr << "File " << fileName2 << " could not be opened.\n";
        exit(1);
    } // end if //        
} // end of Joint constructor //

Joint::~Joint()
{
    jointsBinaryFile.close();
    reactionsBinaryFile.close();
    remove(fileName1);
    remove(fileName2);
    delete [] jointReactionsRecord;
} // end of Joint destructor //

void Joint::write(const intPos &rec) {
    jointsBinaryFile.seekp(sizeOfJointRecord*(rec),ios::beg);
    jointsBinaryFile.write(reinterpret_cast<const char *> (this), sizeOfJointRecord);        
} // end of Joint::write() //

void Joint::read(const intPos &rec) {
    jointsBinaryFile.seekg(sizeOfJointRecord*(rec),ios::beg);
    jointsBinaryFile.read(reinterpret_cast< char *> (this), sizeOfJointRecord);        
} // end of Joint::read() //

void Joint::writeReac(const intPos &rec) {
    reactionsBinaryFile.seekp(sizeOfJointReactionsRecord*(rec),ios::beg);
    reactionsBinaryFile.write(reinterpret_cast<const char *> (this->jointReactionsRecord), sizeOfJointReactionsRecord);        
} // end of Joint::write() //

void Joint::readReac(const intPos &rec) {
    reactionsBinaryFile.seekg(sizeOfJointReactionsRecord*(rec),ios::beg);
    reactionsBinaryFile.read(reinterpret_cast< char *> (this->jointReactionsRecord), sizeOfJointReactionsRecord);        
} // end of Joint::read() //
