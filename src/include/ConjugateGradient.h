// +++++++++++++++++++++++++++++++++++++++++++++++++++
//  Conjugate Gradient method with Preconditioning
//  Algorithm from:
// "An Introdiction to the Conjugate Gradient Method without the Agonizing Pain"
//  by Jonathan Richard Shewchuk
//  pag. 48
//
//  Includes variable bandWidth
//
//  Version 1.0
//  Last Modified Sun Jul 05 12:37:42 2009
//  System: linux
//
//  Copyright (C) 2009
//  Edgar F. Black
//
//  Send comments and requests for help to:
//  edgarfblack@gmail.com


#ifndef CONJUGATEGRADIENT_H
#define CONJUGATEGRADIENT_H

#include <iomanip>
using std::setw;

#include <cmath>
using std::sqrt;

#include <fstream>
using std::ostream;

#include "dimen.h"

#include <numeric>
using std::inner_product;

template <class REAL, class E1, class E2>
void conjGrad(ostream &myout,
              REAL **K,
              REAL *x,
              const E1 &rows,
              E2 *leftCol)
{
//  Local Variables
    REAL *r, *s, *d, *q, *b;
    REAL temp, errorNew, errorOld,error0;
    size_t counter=0;
    const REAL etol = 1.0e-6;
    static size_t *rightCol=nullptr;
//  End of local variables

//   dimensioning arrrays
     dimVec(r,rows);
     dimVec(s,rows);
     dimVec(d,rows);
     dimVec(q,rows);
     dimVec(b,rows);
//   end of dimensioning arrrays


   //static bool firstTime = true;
//   if (firstTime) {
   if (rightCol==nullptr) {
      //cerr << "Pase por aqui!!!\n";
      dimVec(rightCol,rows);
      rightCol[rows] = rows;
      for (size_t i=1;i<=rows ;++i ) {
         for (size_t j=i+1;j<=rows ;++j ) {
            if (leftCol[j] <= i) {
               rightCol[i] = j;
            } // endif //
         } // endfor //
      } // endfor //
      //firstTime = false;
   } // endif //

   for (size_t i=1; i<=rows; ++i) {
      b[i] = x[i];
      x[i] /= K[i][i];      // X0 is f divided by thr main diagonal of k
//       x[i] = 0.0;
   } // endfor //

   for (size_t i=1, k =1; i<=rows ; k = leftCol[++i]) { // use to be matVectMult(k,x,q,n,leftCol);
      q[i] = inner_product( &(K[i][k]),&(K[i][i])+1,&x[k],0.0);
      for (size_t j=i+1; j<=rightCol[i] ;++j ) {
         if (leftCol[j] <= i and K[j][i] !=0.0) {
            q[i] += K[j][i] * x[j];
         } // endif //
      } // endfor //
   } // endfor //
   // matVectMult(k,x,q,n,leftCol);

   for (size_t i=1; i<=rows; ++i) {
      r[i] = b[i] - q[i];
      s[i] = d[i] = r[i]/K[i][i];
   } // endfor //

   errorNew = error0 = inner_product( r+1,r+rows+1,d+1, 0.0);
   while ( errorNew > etol*etol*error0 and counter < rows) {

     for (size_t i=1, k =1; i<=rows ; k = leftCol[++i]) { // use to be matVectMult(k,d,q,n,leftCol);
        q[i] = inner_product( &(K[i][k]),&(K[i][i])+1,&d[k],0.0);
        for (size_t j=i+1; j<=rightCol[i] ;++j ) {
           if (leftCol[j] <= i and K[j][i] !=0.0) {
              q[i] += K[j][i] * d[j];
           } // endif //
        } // endfor //
     } // endfor //
      //matVectMult(k,d,q,n,leftCol);
      temp = errorNew /inner_product( d+1,d+rows+1,q+1, 0.0);
      for (size_t i=1; i<=rows; ++i) {
         x[i] += temp * d[i];
         r[i] -= temp*q[i];
         s[i] = r[i]/K[i][i];
      } // endfor //
      errorOld = errorNew;
      errorNew = inner_product( r+1,r+rows+1,s+1, 0.0);
      temp = errorNew/errorOld;
      for (size_t i=1;i<=rows;++i) {
         d[i] = s[i] + temp * d[i];
      } // endfor //
      ++counter;
   } // endwhile //
   myout << "\n\tNumber of iterations in Conjugate Gradient: " << setw(8)  << counter << '\n';
   freeVec(r);
   freeVec(s);
   freeVec(d);
   freeVec(q);
   freeVec(b);
   if (rightCol!=nullptr) freeVec(rightCol);
} // end conjGrad() //
#endif // End of CONJUGATEGRADIENT_H
