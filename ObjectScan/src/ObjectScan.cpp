// *******************************************************************
// *******************************************************************
// *******************************************************************
// **                                                               **
// **                                                               **
// **                      ObjectScan V 2.03                        **
// **                      =================                        **
// **                                                               **
// **           a free form input C++ subprogram system             **
// **                upper and lower case version                   **
// **                                                               **
// **                                                               **
// *******************************************************************
//
//                    Last update: Wed 12 Aug 2009 12:55:04 CDT 
//
// *******************************************************************
//
//               questions may be addressed to :
//               Edgar F. Black -- email edgarfblack@gmail.com
//
//-----------------------------------------------------------------------------
//  Here is the alphabetic list of the ObjectScan system functions:
//  backsp()                    done
//  doscan()                    done
//  endcrd()                    done
//  endstr()                    done
//  floatn()                    done
//  getEcho()			        done
//  getOutputFileName()         done
//  getstr()                    done
//  in_from_stdin()		        done ! former in_from_remote()
//  integr()                    done
//  isStdinKybrd()              done
//  isStdoutScreen()		    done
//  isstring()                  done
//  label()                     done
//  matchs()                    done
//  matchs_exact()              done
//  name()                      done
//  numd()                      done
//  numf()                      done
//  numi()                      done
//  out_to_stdout()             done
//  readLine()			        done ! former readsc()
//  reset()                     done
//  scan_contents()             done
//  sep()                       done
//  setInputFile(filename)	    done ! former open_input_file()
//  setInputFile()		        done ! Overloaded version of setInputFile(filename)
//  setOutputFile(filename)     done
//  setOutputFile()             done ! Overloaded version of setOutputFile(filename)
//  setEcho()			        done ! now renamed setEcho()
//  sizlst()                    done
//  skpstr()                    done
//  trlist()                    done
//  trxlist()                   done ! the arguments for this function has been changed
//  getObjectScanVersion()	    done
// _____________________________________________________
//  init_scan()			not needed any more. The class constructor do the house keeping now.
//  istrue()			not needed any more
//---------------------------------------------------------------------


#include "ObjectScan.h"



Scan::Scan(const positiveInt &LineW,
           const positiveInt &MaxTk,
           const char *charEOL,
           const bool &echo,
           const positiveInt &MaxInpF,
           const char *sep)  :  MaxTkPerLine{MaxTk},
                                LineWith{LineW},
                                MaxInpFiles{MaxInpF},
                                echoLine{echo},
                                is_stdin_kybrd   {static_cast<bool> (isatty(fileno(stdin  )))},
                                is_stdout_screen {static_cast<bool> (isatty(fileno(stdout )))}
{

    if (!is_stdin_kybrd or !is_stdout_screen) {
        cerr << "\tObjectScan does not allow input or output to be redirectioned....\n";
        exit(-1);
    } // end if //
    
    setEcho(echo);
    token =(char **) new char* [MaxTkPerLine];
    line = new char[LineWith+1];
    strcpy(separator,sep);
    strcpy(eolChar,charEOL);
    myInputFiles =(fstream **) new fstream* [MaxInpFiles];
    numberOfInputFilesOpened = 0;
    readyToMove=false;
    is_comming_from_file=false;
    StringLength=0;
    tokenPerLine=0;
    prompt = is_stdin_kybrd;
    myStdIn  = cin.rdbuf();
    myStdOut = cout.rdbuf();
    //   Screen = clog.rdbuf();
} // end of Scan::Scan() constructor //

Scan::~Scan()
{
  //cout << "Scan Destructor running\n";
  
  for (positiveInt file=0; file <numberOfInputFilesOpened; ++file ) {
      myInputFiles[file]->close();
      delete myInputFiles[file];  
  } // end for //
  delete [] myInputFiles;
  
  delete [] line;
  currentToken=nullptr;
  delete [] token;  
  if (myOutputFile.is_open()) {
//      myOutputFile.close();
//      cout.rdbuf(myStdOut);
      out_to_stdout();
  } // end if //  
} // end of Scan:~:Scan() destructor //

