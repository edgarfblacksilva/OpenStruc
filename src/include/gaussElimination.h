#ifndef GAUSELIMINATION_H
#define GAUSELIMINATION_H
#include <iostream>

#include <fstream>
using std::ostream;

#include <cmath>
using std::sqrt;

#include <numeric>
using std::inner_product;

//#include <algorithm>
//using std::max;
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

#include "dimen.h"

// ++++++++++++++++++++++++++++++++++++++++++++
//       t
//   L D L Solution based on Gauss Elimination
//   The active "Row" solution
//   Variation of the algorithm from "Finite Elements Procedures" by Klaus Bathe
//   pag:  708 - 716.
//   Includes variable bandWidth
//   Version 1.0
//   Last Modified 28 Apr 2006 11:14:40
//   System: OS/2
//
//   Copyright (C) 2005
//   Edgar F. Black
//
//   Send comments and requests for help to:
//   edgarfblack@gmail.com

template <class REAL, class E1, class E2>
void ldl   (ostream &myout,REAL **matrix, REAL *vector, const E1 &rows, E2 *leftCol, const bool &acction,const bool &eigen)
{

  static bool reduced = false;
  size_t i,j,k;
  double temp;


  if (acction) {
    double temp1;
    for (i=2; i <= rows ; ++i) {
      const size_t jj = leftCol[i];
      for (j=jj+1; j < i ; ++j) {
        k = MAX(jj, leftCol[j]);
        matrix[i][j] -= inner_product(&matrix[j][k] , &matrix[j][j] ,&matrix[i][k] , 0.0 );
      } // endfor //

      for (j=jj, temp = 0.0; j<i ;++j) {
        temp1 = matrix[i][j] / matrix[j][j];
        temp += temp1 * matrix[i][j];
        matrix[i][j] = temp1;
      } // endfor //
      matrix[i][i] -= temp;
      if (matrix[i][i] <= 0.0) {
        if (!eigen) {  // regular case. a zero or a negative value on the diagonal stop the process
          myout << "LDL decmposition failed.\n"
        << "Stffness Matrix not positive definite\n"
        << "Non Positive pivot for equation: " << i << '\n';
          exit(1);
        } else {                    // used for eigensolvers for looking for zeros or
          if (matrix[i][i] == 0) { // negative values on the main diagonal
            matrix[i][i] = -1.0e-16;
          } // endif //
        } // endif //
      } // endif //
    } // endfor //
    reduced = true;
  } else {
    if (!reduced) {
      myout << "STOP!!!  The matrix has NOT being reduced yet.\n";
      exit(0);
    } // endif //
    // forward
    for (i=1; i<=rows ; ++i) {
      j = leftCol[i];
      vector[i] -= inner_product(&matrix[i][j] , &matrix[i][i] , &vector[j], 0.0 );
    } // endfor //

    // backward
    size_t *rightCol;
    dimVec(rightCol,rows);
    rightCol[rows] = rows;
    for (size_t i=1;i<=rows ;++i ) {
      for (size_t j=i+1;j<=rows ;++j ) {
        if (leftCol[j] <= i) {
          rightCol[i] = j;
        } // endif //
      } // endfor //
    } // endfor //


    for (i = rows; i >= 1 ; --i) {
      vector[i] /= matrix[i][i];
      j = leftCol[i];
      //         for (k=i+1, temp = 0.0;  k<=rows; ++k ) {
      for (k=i+1, temp = 0.0;  k<=rightCol[i]; ++k ) {
        if (leftCol[k]  <= i) {
          temp += (matrix[k][i] * vector[k]);
        } // endif //
      } // endfor //
      vector[i] -= temp;
    } // endfor //
    freeVec(rightCol);
  } // endif //
}

template <class REAL, class E1, class E2>
void ldl   (ostream &myout,REAL **matrix,  const E1 &rows, E2 *leftCol)
{
  REAL *voidPtr=nullptr;
  ldl(myout, matrix,voidPtr, rows, leftCol,true,false);    // Factorization of matrix 'matrix'
}


template <class REAL, class REAL2, class E1, class E2>
void ldl   (ostream &myout,REAL **matrix, REAL2 *vector, const E1 &rows, E2 *leftCol)
{
  ldl(myout,matrix,vector, rows, leftCol,false,false);   // Reducing right-hand-side load vector 'vector'
}

template <class REAL, class E1, class E2>
void ldlEgn (ostream &myout,REAL **matrix,  const E1 &rows, E2 *leftCol)
// the purpuse of the ldlEgn function is to be used for eigensolvers
// to look for zeros or negative numbers on the main diagonal.
// Notice that the last argument is set to true to instruct ldl()
// to permit for zero or negative values on the main diagonal.
{
  REAL *voidPtr=nullptr;
  ldl(myout, matrix,voidPtr, rows, leftCol,true,true);    // Factorization of matrix 'matrix'
}


// ++++++++++++++++++++++++++++++++++++++++++++
//   Cholesky Factorizaton.
//   Variation of the algorithm from "Matrix Structural Analysis" by McGuire, Gallagher & Ziemian
//   pag:  307 - 309.
//   Includes variable bandWidth
//   Version 1.0
//   Last Modified 29 Apr 2006 10:30:43
//   System: OS/2
//
//   Copyright (C) 2005
//   Edgar F. Black
//
//   Send comments and requests for help to:
//   edgarfblack@insightbb.com


template <class REAL, class E1, class E2>
void mycholes(ostream &myout,REAL **matrix, REAL *vector, const E1 &rows, E2 *leftCol, const bool &acction)
{
  size_t i,j,k;
  double temp;
  static bool reduced = false;

  if (acction) {
    for (i=1; i <= rows ; ++i) {
      j = leftCol[i];
      temp = (matrix[i][i]);
      temp  -= inner_product(&(matrix[i][j]) , &(matrix[i][i]) ,&(matrix[i][j]) , 0.0 );
      if (temp > 0) {
        // matrix[i][i] = 1.0/sqrt(temp);
        matrix[i][i] = sqrt(temp);
      } else {
        myout << "Cholesy decmposition failed.\n"
              << "Stffness Matrix not positive definite\n"
              << "Non Positive pivot for equation: " << i;
        exit(1);
      } // endif //
      for (j=i+1; j<=rows ; ++j) {
        if (leftCol[j] > i) {
          continue;
        } // endif //
        k = MAX(leftCol[j], leftCol[i]);
        matrix[j][i] -= inner_product(&matrix[i][k] , &(matrix[i][i]) , &(matrix[j][k]), 0.0 );
        //            matrix[j][i] *=  matrix[i][i];
        matrix[j][i] /=  matrix[i][i];
      } // endfor //
    } // endfor //
    reduced = true;
  } else {
    if (!reduced) {
      myout << "STOP!!!  The matrix has NOT being reduced yet.\n";
      exit(0);
    } // endif //
    // forward
    for (i=1; i<=rows ; ++i) {
      j = leftCol[i];
      vector[i] -= inner_product(&matrix[i][j] , &matrix[i][i] , &vector[j], 0.0 );
      //         vector[i] *= matrix[i][i];
      vector[i] /= matrix[i][i];
    } // endfor //

    // backward
    for (i = rows; i >= 1 ; --i) {
      j = leftCol[i];
      for (k=i+1, temp = 0.0; k<=rows ; ++k ) {
        if (leftCol[k]  <= i) {
          temp += (matrix[k][i] * vector[k]);
        } // endif //
      } // endfor //
      // vector[i] = (vector[i] - temp) * matrix[i][i];
      vector[i] = (vector[i] - temp) / matrix[i][i];
    } // endfor //
  } // endif //

}

template <class REAL, class E1, class E2>
void choles(ostream &myout,REAL **matrix,  const E1 &rows, E2 *leftCol)
{
  REAL *voidPtr;
  mycholes(myout, matrix,voidPtr, rows, leftCol,true);    // Factorization of matrix 'matrix'
}


template <class REAL, class REAL2, class E1, class E2>
void choles(ostream &myout,REAL **matrix, REAL2 *vector, const E1 &rows, E2 *leftCol)
{
  mycholes(myout,matrix,vector, rows, leftCol,false);   // Reducing right-hand-side load vector 'vector'
}

// Mas abajo estan LDLt y choleski para reducir matrices con ancho de banda constante...


// ++++++++++++++++++++++++++++++++++++++++++++
//       t
//   L D L Solution based on Gauss Elimination
//   The active "Row" solution
//   Variation of the algorithm from "Finite Elements Procedures" by Klaus Bathe
//   pag:  708 - 716.
//   constant bandWidth (bandW)
//   Version 1.0
//   Last Modified 25 Mar 2005 7:15:37
//   System: OS/2
//
//   Copyright (C) 2005
//   Edgar F. Black
//
//   Send comments and requests for help to:
//   edgarfblack@insightbb.com

template <class REAL, class E1, class E2, class E3>
void ldl   (ostream &myout,REAL **matrix, REAL *vector, const E1 &rows, const E2  &bandW,   const E3 &acction)
{
  size_t i,j,k;
  double temp;

  switch (acction) {
  case 1:
    double temp1;

    matrix[1][1] = 1.0/matrix[1][1];
    for (i=2; i <= rows ; ++i) {
      if (i<= bandW) {
        k=1;
      } else {
        k=i+1-bandW;
      } // endif //

      for (j=k+1; j < i ; ++j) {
        matrix[i][j] -= inner_product(&matrix[j][k], &matrix[j][j] , &matrix[i][k], 0.0 );
      } // endfor //

      for (j=k, temp = 0.0; j<i ;++j) {
        temp1 = matrix[i][j] * matrix[j][j];
        temp += temp1 * matrix[i][j];
        matrix[i][j] = temp1;
      } // endfor //
      matrix[i][i] -= temp;

      if (matrix[i][i] <= 0) {
        myout << "LDL decmposition failed.\n"
              << "Stffness Matrix not positive definite\n"
              << "Non Positive pivot for equation: " << i << '\n';
        exit(1);
      } else {
        matrix[i][i] = 1.0/matrix[i][i];
      } // endif //
    } // endfor //
    break;
  case 2:
    // forward
    for (i=1; i<=rows ; ++i) {
      if (i<= bandW) {
        j=1;
      } else {
        j=i+1-bandW;
      } // endif //
      vector[i] -= inner_product(&matrix[i][j] , &matrix[i][i] , &vector[j], 0.0 );
    } // endfor //

    // backward
    for (i = rows; i >= 1 ; --i) {
      vector[i] *= matrix[i][i];
      j =  i+bandW-1;
      if (j > rows) {
        j = rows;
      } // endif //
      for (k=i+1, temp = 0.0 ;  k <= j ; ++k ) {
        temp += (matrix[k][i] * vector[k]);
      } // endfor //
      vector[i] -= temp;
    } // endfor //
    break;
  default:
    myout << "option not recognized for LDLt decomposition.\n";
    exit(1);
    break;
  } // endswitch //
}

// ++++++++++++++++++++++++++++++++++++++++++++
//   Cholesky Factorizaton.
//   Variation of the algorithm from "Matrix Structural Analysis" by McGuire, Gallagher & Ziemian
//   pag:  307 - 309.
//   Constant bandWidth (bandW)
//   Version 1.0
//   Last Modified 25 Mar 2005 7:15:37
//   System: OS/2
//
//   Copyright (C) 2005
//   Edgar F. Black
//
//   Send comments and requests for help to:
//   edgarfblack@insightbb.com


template <class REAL, class E1, class E2, class E3>
void choles(ostream &myout,REAL **matrix, REAL *vector, const E1 &rows, const E2  &bandW,   const E3 &acction)
{
  const size_t limit=rows+1-bandW;
  size_t i,j,k;
  size_t ik,jj;
  size_t reducedV=bandW-1;

  double temp;

  switch (acction) {
  case 1:
    for (i=1, j=1; i <= rows ; ++i) {
      temp = matrix[i][i];
      temp -= inner_product(&(matrix[i][j]) , &(matrix[i][i]) , &(matrix[i][j]), 0.0 );
      if (temp > 0) {
        matrix[i][i] = 1.0/sqrt(temp) ;
      } else {
        myout << "Cholesy decmposition failed.\n"
              << "Stffness Matrix not positive definite\n"
              << "Non Positive pivot for equation: " << i;
        exit(1);
      } /* endif */
      for (k=1;k<=reducedV ; ++k) {
        ik=i+k;
        if (ik <= bandW) {
          jj=1;
        } else {
          jj=ik+1-bandW;
        } // endif //
        matrix[ik][i] -= inner_product(&(matrix[i][jj]) , &(matrix[i][i]) , &(matrix[ik][jj]), 0.0 );
        matrix[ik][i] *=  matrix[i][i];
      } // endfor //
      if (i>=limit) {
        --reducedV;
      } // endif //
      if (i >= bandW) {
        ++j;
      } // endif //
    } // endfor //
    break;
  case 2:
    // forward
    for (i=1; i<=rows ; ++i) {
      if (i<= bandW) {
        j=1;
      } else {
        j=i+1-bandW;
      } // endif //
      vector[i] -= inner_product(&matrix[i][j] , &matrix[i][i] , &vector[j], 0.0 );
      vector[i] *= matrix[i][i];
    } // endfor //

    // backward
    jj = bandW-1;
    for (i = rows; i >= 1 ; --i) {
      temp = 0;
      k=i+1;
      for (j=1 ;j<= jj ; ++j, ++k) {
        if (k > rows) {
          break;
        } // endif //
        temp += (matrix[k][i] * vector[k]);
      } // endfor //
      vector[i] = (vector[i] - temp) * matrix[i][i];
    } // endfor //
    break;
  default:
    myout << "option not recognized for Cholesky decomposition.\n";
    exit(1);
    break;
  } // endswitch //
}
#endif // End of GAUSELIMINATION_H
