#ifndef SOLVER
#define SOLVER

#define LDL
//#define CHOLESKY

  #if defined (LDL)
     #include "gaussElimination.h"
  #elif defined (CHOLESKY)
     #include "gaussElimination.h"
  #else
     #include "ConjugateGradient.h"
  #endif
#endif


