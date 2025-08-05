#ifndef OBJECTSCAN_H
#define OBJECTSCAN_H
// set flags for Windows or Unix (C++,g++).
#define UNIX


#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::clog;
using std::endl;
using std::flush;
using std::ios;

#include <iomanip>
using std::setw;
          
#include <fstream>
using std::streambuf;
using std::fstream;


#include <cstring>
using std::string;

#include <cstdio>

#include <cstdlib>

#include <cctype>

#ifdef UNIX
  #include <unistd.h>
#else
  #include <io.h>
#endif

using positiveInt = unsigned int;

class Scan {
   public:
   
      void ScanDebug();
           ~Scan();

       Scan(const positiveInt & = 256,
            const positiveInt & = 50,
            const char   * = "$",
            const bool   & = true,
            const positiveInt & = 10,
            const char   * = " ");
            
      void backsp(const positiveInt & = 1);
      inline void doScan() { currentToken = token[++tokenIndex]; readyToMove=false;}
      inline bool endcrd() { return (tokenIndex >= tokenPerLine); }
      bool endstr();
      bool floatn(float &);
      inline bool getEcho() {return echoLine;}
      inline void getstr() { currentStringPos = 1; }
      inline float getObjectScanVersion() {return(Version/100.0);}
      void in_from_stdin();
      bool integr(int &);
      
      inline bool isStdinKybrd() {return (numberOfInputFilesOpened == 0 ? true : false);}
      inline bool isStdoutScreen() {return !myOutputFile.is_open();}

      bool isstring();
      bool label();
      bool matchs(const char *, const positiveInt &);
      bool matchs_exact(const char *);
      bool name();
      bool numd(double &);
      bool numf(float &);
      bool numi(int &);
      void out_to_stdout();
      bool readLine();
      inline void reset()  { tokenIndex=0; currentToken = token[0]; readyToMove=false;}
      void scan_contents(char *, positiveInt &);
      bool sep(positiveInt &);
      //bool sep(int    &);
      bool setInputFile(const char *);
      inline bool setInputFile() {return setInputFile(currentToken);}
      bool setOutputFile(const char *);
      inline string getOutputFileName(){return OutFileName;}
      inline bool setOutputFile(){return setOutputFile(currentToken); }
      inline void setEcho(const bool &echo){ echoLine=echo;}
      int sizlst (const int *, const int &);
      inline void skpstr() { currentStringPos = StringLength+1;}
      void trlist (int *, const positiveInt &, const int &, positiveInt &, int & );
      void trxlst (int &, int &,  int *, const positiveInt & );
      inline positiveInt getLineCounter(){return LineCounter;}

   private:
      char *toLowerStr(char *, const positiveInt &);
      void updateInputFile(const positiveInt &);
      positiveInt MaxTkPerLine;  
      positiveInt LineWith;
      positiveInt LineCounter=0;
      
      //char *separator=nullptr;
      //char *eolChar=nullptr;

      char separator[2] = {'\0','\0'};
      char eolChar[2] = {'\0','\0'};
      
      static const char separray[];
      positiveInt tokenIndex;
      positiveInt tokenPerLine;
      positiveInt StringLength;
      positiveInt currentStringPos;
      const positiveInt MaxInpFiles;
      positiveInt numberOfInputFilesOpened;
      char *line=nullptr; 
      char **token;
      char *currentToken=nullptr;
      bool prompt;
      bool readyToMove;
      bool echoLine;
      bool is_comming_from_file;
      const bool is_stdin_kybrd;
      const bool is_stdout_screen;
      string OutFileName;
      
      fstream **myInputFiles;
      fstream myOutputFile;
      streambuf *myStdIn;
      streambuf *myStdOut;
   //   streambuf *Screen;
      
      static const unsigned short Version=203;
};
#endif
